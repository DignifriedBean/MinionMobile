# MinionMobile

UE5.8 Android-compatible sample project that creates a floor and exactly 100 minions using only Unreal Engine built-in primitive meshes.

## Scene

- The floor is spawned from `/Engine/BasicShapes/Cube.Cube`.
- Each minion is assembled from built-in sphere and cube primitives.
- The game mode spawns a deterministic 10 x 10 grid and asserts that the spawned minion count is exactly 100.
- No imported assets are included; the project has no `Content` asset payload.

## Android/mobile configuration

The project uses conservative mobile-friendly settings in `Config/DefaultEngine.ini`:

- Mobile HDR disabled.
- Forward shading enabled.
- Bloom, motion blur, auto exposure, ambient occlusion, distance fields, and stationary skylight support disabled.
- Android package ID set to `com.codex.minionmobile`.
- ARM64 enabled, ARMv7 disabled.
- Min SDK 26, target SDK 35.
- Vulkan enabled, Vulkan SM5 disabled.

## Validation

Run the validation script from the project root:

```powershell
powershell -ExecutionPolicy Bypass -File .\Scripts\Validate-AndroidConfig.ps1
```

Full editor/build validation requires a local Unreal Engine 5.8 installation.
