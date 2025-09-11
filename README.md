# MJSDL

SDL3 + RAII + a couple of toys.

C++14 minimum required.

<!--ts-->
* [MJSDL](#mjsdl)
   * [What?](#what)
   * [How?](#how)
      * [Implementation Details](#implementation-details)
      * [Huh? (example)](#huh-example)
         * [SDL, uncut](#sdl-uncut)
         * [Some mjsdl](#some-mjsdl)
         * [Full mjsdl](#full-mjsdl)
         * [Another mjsdl example](#another-mjsdl-example)
   * [Guards](#guards)
   * [Why?](#why)

<!-- Created by https://github.com/ekalinin/github-markdown-toc -->
<!-- Added by: mumbly, at: Thu 11 Sep 2025 12:44:17 AEST -->

<!--te-->

## What?

`mjsdl` is simply a SDL3 wrapper for RAII (lifetime safety) in C++, with a couple of
small kindnesses thrown in for shiggles. It does not, nor should it, replace all
of the SDL library with wrappers, only the types where it makes sense.

The goal is to have as small a surface as possible, that can be used with
minimal changes to working code. It will not get you out of reading the SDL
documentation, doing error checking, or anything else.

Being inline header-only code, you will find that with even minimal
optimisations enabled all of the `mjsdl` code vanishes in the generated output
when using the simplest drop-in replacement style.

## How?

Many of the SDL types have a cycle of Create/Destroy or Acquire/Release
functions. These are replaced by C++ move-only classes taking care of this with
RAII.

All classes have:
* Default constructors that begin the object uninitialised.
* A constructor that takes the exact arguments of the SDL creation function.
* Constructors that take the SDL type (and others needed for destruction) are
supplied to interface with other libraries or existing code.
* `get()` to access the underlying SDL type.
* `is_valid()` to test the underlying type isn't null.
* `release()` to give up ownership of the SDL type, it must then be deleted
manually or by other code.

They may optionally have:
* Additional constructors to cheat a little, such as avoiding \*CreateInfo
objects with only two fields.
* Helper methods, say if an item is really only used to do a couple of things.
And example is `mjsdl::GPUTransferBuffer` has `map()` and `unmap()` methods.

### Implementation Details

All constructors have an optional guard object. Check that out at
[#Guards](#Guards). It's zero-cost and does nothing by default, you can simply
ignore this feature and continue error checking however you like, if at all,
It's your code.

Sometimes SDL types are created and destroyed via another item (`SDL_GPUBuffer`
takes `SDL_GPUDevice` at creation and destruction for example). Since in these
cases the item is always used at creation and destruction, `mjsdl` classes
simply hold on to it in a non-owning pointer until destruction. You need to do
nothing, and it costs only a few bytes.

Classes always have a `get()` and a `is_valid()` method, to get the internal
SDL type and to test if it is nullptr. I have decided it is better to be
explicit rather than rely on overloading operators to do the same things, such
as `std::optional` does - it's clearer and we aren't paying by the letter.

If a method returns memory that needs to be freed by `SDL_free` it will be
wrapped up in a `std::unique_ptr` with a custom deleter.

Yes it's a lot of boilerplate. You may notice a generator directory, most
classes are generated using a python script and a template. This makes
additions and modifications trivial. Don't worry, the git repo always comes
with files pre-generated, you don't need to generate anything unless you wish
to make changes.

### Huh? (example)

#### SDL, uncut

```cpp
SDL_Window *window = SDL_CreateWindow("Pure SDL", 800, 600, SDL_WINDOW_RESIZABLE);
if (!window)
{
    throw std::runtime_error{SDL_GetError()};
}

SDL_GPUDevice *device = SDL_CreateGPUDevice(
    SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true, nullptr);
if (!device)
{
    SDL_DestroyWindow(window);
    throw std::runtime_error{SDL_GetError()};
}

if (!SDL_ClaimWindowForGPUDevice(device, window))
{
    SDL_DestroyGPUDevice(device);
    SDL_DestroyWindow(window);
    throw std::runtime_error{SDL_GetError()};
}

SDL_DestroyGPUDevice(device);
SDL_DestroyWindow(window);
```

#### Some mjsdl

```cpp
mjsdl::Window window{"Some mjsdl", 800, 600, SDL_WINDOW_RESIZABLE};
if (!window.is_valid())
{
    throw std::runtime_error{SDL_GetError()};
}

mjsdl::GPUDevice device{SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true,
                        nullptr};
if (!device.is_valid())
{
    throw std::runtime_error{SDL_GetError()};
}

if (!SDL_ClaimWindowForGPUDevice(device.get(), window.get()))
{
    throw std::runtime_error{SDL_GetError()};
} 
```

#### Full mjsdl

```cpp
mjsdl::guard_throws guard;
mjsdl::Window window{"Full mjsdl", 800, 600, SDL_WINDOW_RESIZABLE, guard};
mjsdl::GPUDevice device{SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true,
                        nullptr, guard};
guard(SDL_ClaimWindowForGPUDevice(device.get(), window.get()));
```

#### Another mjsdl example

```cpp
std::pair<mjsdl::Window, mjsdl::GPUDevice> buildsdl()
{
    // Remember, in deep functions white space is your friend.

    auto guard = [](bool value) {
        if (value) return;
        const char *error = SDL_GetError();
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in buildsdl: %s", error);
        throw mjsdl::ctor_error{error};
    };

    mjsdl::Window window{"Just spitballing", 800, 600, SDL_WINDOW_RESIZABLE, guard};
    mjsdl::GPUDevice device{SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true,
                            nullptr, guard};

    guard(SDL_ClaimWindowForGPUDevice(device.get(), window.get()));

    return {std::move(window), std::move(device)};
}

void wrap_example()
{
    // Reduce cognitive load for the new guys, they don't need to see the details yet.
    auto [window, device] = buildsdl();
}
```

## Guards

Every constructor can take a guard object in case of errors.

Currently two guard types are supplied:
* `mjsdl::guard_noop` *(default)* - Does literally nothing, and will be
optimised away. You will still need to do the usual tests with `is_valid()`,
just like you would have using C pointers.
* `mjsdl::guard_throws` - Throw a `mjsdl::ctor_error` exception type with the
`SDL_GetError()` message, accessed as usual with `what()`. Yes yes exceptions
hurt your feelings, it's an option, and makes for very very clean code without
all the error checks.

You can write custom guard types, or pass a lambda. Basically anything that can
be called with the SDL type (a pointer) and check it for validity. Taking it as
a bool argument is easiest, but you do you.

You can override the default locally, globally, or per compilation unit, by
defining `MJSDL_GUARD_DEFAULT`. Of course whatever you define it as must be
available at the time of including `mjsdl` headers. `mjsdl::guard_throw` is an
easy example, and is used as such in the `testharness` application.

```cmake
target_compile_definitions(testharness PUBLIC -DMJSDL_GUARD_DEFAULT=mjsdl::guard_throws)
```

## Why?

1. Remembering to destroy a pile of items in the reverse order they were
   created in and when errors and exceptions occur is a pain in the ass. We can
   use RAII, move semantics, C compatibility, type safety, and more to solve these
   issues - may as well use them in as non-intrusive a way as possible.
2. Error checking is a dick for C libraries, taking away the burden with
   dependency injected templated guard objects with overloaded operators sounds
   like a nightmare but it's really simple in practice, low effort, and zero-cost
   by default with the no-op guard.
