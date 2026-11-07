# GL no BS
> No unnecessary abstractions. No hidden magic. Just OpenGL.

An OpenGL auxiliar library for OpenGL made in C++20, with external contexts and loaders.

## Building
Requirements:
* A C++20 compiler of choice.
* CMake 3.20+.
* Ninja.

### Step 01:

```bash
./scripts/build.sh
```

To also build the tests and run them:
```bash
./scripts/build.sh --tests
ctest --test-dir build --output-on-failure
```

The output is the static library `build/libglpp.a`.

## Status
At a very very very early stage.

## License
MIT, see [LICENSE](LICENSE).