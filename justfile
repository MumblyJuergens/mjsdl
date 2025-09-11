set unstable

default:
    @just --list

# TODO: Windows version with "py".

# Build the python vitrual environment and install need pips there.
[unix, script, working-directory: 'generator']
generator-create-venv:
    python -m venv venv
    source venv/bin/activate
    pip install jinja2
    pip install python-rapidjson

# Run the JSON -> CPP generator.
[unix, script, working-directory: 'generator']
generate:
    source venv/bin/activate
    python gen_mjsdl.py

[unix]
gogogo:
    rm -rf build
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    cmake --install build --prefix /home/mumbly/code/instalol
