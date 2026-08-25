# WebAssembly Bridge

This directory will contain Emscripten build glue and the thin TypeScript-facing wrapper for the stable Driveform C API.

Phase 0 target:

1. compile the same `DriveformCore` + `DriveformC` to WASM;
2. create/destroy a world in the browser;
3. run the fixed-step smoke path;
4. expose version / step count to `Web/Editor`;
5. keep all actual vehicle dynamics in C++ rather than reimplementing them in TypeScript.
