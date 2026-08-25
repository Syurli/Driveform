# Unreal Integration

Target host: **Unreal Engine 5.8 + Chaos**.

Planned responsibilities:

- Chaos implementation of `IPhysicsBackend`
- `UDriveformVehicleComponent`
- Driveform asset import/binding
- Blueprint input/state API
- wheel/track visual binding
- debug draw, audio/VFX hooks
- later network/replication bridge

The integration layer must not move vehicle dynamics back into Unreal-specific code.
