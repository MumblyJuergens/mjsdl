"""Builds mjsdl classes from input JSON"""

import rapidjson
import os
from jinja2 import Environment, FileSystemLoader
from collections import namedtuple

CPPType = namedtuple("CPPType", ["name", "type", "store", "dtor_arg"])

env = Environment(loader=FileSystemLoader("templates"))
headers = []


def process_data_files() -> None:
    for file in os.listdir("data"):
        go(os.path.join("data", file))

    with open(
        "../include/mjsdl/generated.hpp", mode="w", encoding="utf-8"
    ) as headerout:
        print("#pragma once", file=headerout)
        for header in headers:
            print(f'#include "{header}.hpp"', file=headerout)

    template = env.get_template("generated.cmake.jinja")
    output = template.render(
        headers=headers,
    )
    with open(
        "../cmake/generated.cmake", mode="w", encoding="utf-8"
    ) as cmakeout:  # lol make out
        print(output, file=cmakeout)
    
    template = env.get_template("fwd.hpp.jinja")
    output = template.render(
        headers=headers,
    )
    with open(
        "../include/mjsdl/fwd.hpp", mode="w", encoding="utf-8"
    ) as cmakeout:  # lol make out
        print(output, file=cmakeout)



def go(filename: str) -> None:

    with open(filename) as jsonfile:
        data = rapidjson.load(
            jsonfile, parse_mode=rapidjson.PM_COMMENTS | rapidjson.PM_TRAILING_COMMAS
        )

    for cpp in data:
        cpp_name = cpp["name"]
        prefix=cpp.get("prefix", "SDL_")
        sdl_type = cpp.get("sdl_type", f"{prefix}{cpp_name} *")
        sdl_ctor_verb = cpp.get("ctor_verb", "Create")
        sdl_dtor_verb = cpp.get("dtor_verb", "Destroy")
        extra_headers = cpp.get("extra_headers", [])
        no_ctor = True
        no_default_ctor = cpp.get("no_default_ctor", False)
        no_native_ctor = cpp.get("no_native_ctor", False)
        no_dtor = cpp.get("no_dtor", False)
        min_sdl_version = cpp.get("min_sdl_version", "3, 2, 0")
        guard_defines = cpp.get("guard_defines", [])
        namespace = cpp.get("namespace", "mjsdl")

        headers.append(cpp_name)

        toys = "// none for this class :("
        if "toys" in cpp:
            with open(cpp["toys"], "r") as toyfile:
                toys = toyfile.read()

        ctor_args: list[CPPType] = []
        if "ctor_args" in cpp:
            no_ctor = False
            for arg in cpp["ctor_args"]:
                ctor_args.append(
                    CPPType(
                        name=arg["name"],
                        type=arg["type"],
                        store=arg.get("store", False),
                        dtor_arg=arg.get("dtor_arg", False),
                    )
                )
        has_init_list = len([p for p in ctor_args if p.store]) > 0

        template = env.get_template("SDLClass.jinja")
        output = template.render(
            cpp_name=cpp_name,
            sdl_type=sdl_type,
            sdl_dtor_verb=sdl_dtor_verb,
            sdl_ctor_verb=sdl_ctor_verb,
            extra_headers=extra_headers,
            toys=toys,
            ctor_args=ctor_args,
            has_init_list=has_init_list,
            no_ctor=no_ctor,
            no_default_ctor=no_default_ctor,
            no_native_ctor=no_native_ctor,
            no_dtor=no_dtor,
            min_sdl_version=min_sdl_version,
            guard_defines=guard_defines,
            namespace=namespace,
            prefix=prefix
        )

        with open(
            f"../include/mjsdl/{cpp_name}.hpp", mode="w", encoding="utf-8"
        ) as headerout:
            print(output, file=headerout)
        os.system(f"clang-format -i -style=file ../include/mjsdl/{cpp_name}.hpp")


if __name__ == "__main__":
    process_data_files()
