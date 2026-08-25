import { useEffect, useRef } from 'react'
import * as THREE from 'three'

function Viewport() {
  const hostRef = useRef<HTMLDivElement | null>(null)

  useEffect(() => {
    const host = hostRef.current
    if (!host) return

    const scene = new THREE.Scene()
    scene.background = new THREE.Color(0x11161d)

    const camera = new THREE.PerspectiveCamera(45, 1, 0.1, 100)
    camera.position.set(5.2, 3.4, 6.2)
    camera.lookAt(0, 0.6, 0)

    const renderer = new THREE.WebGLRenderer({ antialias: true })
    renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2))
    host.appendChild(renderer.domElement)

    const grid = new THREE.GridHelper(12, 24, 0x39424d, 0x242b33)
    scene.add(grid)

    const chassis = new THREE.Mesh(
      new THREE.BoxGeometry(3.6, 0.65, 1.8),
      new THREE.MeshStandardMaterial({ color: 0x88939f, roughness: 0.65 }),
    )
    chassis.position.y = 0.85
    scene.add(chassis)

    const turret = new THREE.Mesh(
      new THREE.BoxGeometry(1.45, 0.5, 1.25),
      new THREE.MeshStandardMaterial({ color: 0xa0aab4, roughness: 0.7 }),
    )
    turret.position.set(0.35, 1.45, 0)
    scene.add(turret)

    const key = new THREE.DirectionalLight(0xffffff, 2.4)
    key.position.set(4, 8, 5)
    scene.add(key)
    scene.add(new THREE.HemisphereLight(0xcfe0ff, 0x30343a, 1.4))

    const resize = () => {
      const width = host.clientWidth
      const height = host.clientHeight
      renderer.setSize(width, height, false)
      camera.aspect = Math.max(width / Math.max(height, 1), 0.1)
      camera.updateProjectionMatrix()
    }

    resize()
    const observer = new ResizeObserver(resize)
    observer.observe(host)

    let frame = 0
    const animate = () => {
      frame = requestAnimationFrame(animate)
      chassis.rotation.y += 0.0015
      turret.rotation.y = chassis.rotation.y * 0.4
      renderer.render(scene, camera)
    }
    animate()

    return () => {
      cancelAnimationFrame(frame)
      observer.disconnect()
      renderer.dispose()
      host.removeChild(renderer.domElement)
    }
  }, [])

  return <div className="viewport" ref={hostRef} />
}

const systems = ['Vehicle Body', 'Powertrain', 'Engine', 'Clutch', 'Gearbox', 'Differential', 'Suspension', 'Track L / R']

export default function App() {
  return (
    <main className="app-shell">
      <header className="topbar">
        <div>
          <strong>驭形 Driveform</strong>
          <span>Vehicle Dynamics Studio · v0.1 foundation</span>
        </div>
        <div className="status"><i /> Core/WASM pending</div>
      </header>

      <aside className="panel tree-panel">
        <h2>System Tree</h2>
        <ul>{systems.map((item) => <li key={item}>{item}</li>)}</ul>
      </aside>

      <section className="stage">
        <div className="stage-title">DF-Track-01 · Reference View</div>
        <Viewport />
      </section>

      <aside className="panel inspector-panel">
        <h2>Inspector</h2>
        <label>Fixed Step<input value="120 Hz" readOnly /></label>
        <label>Simulation Profile<input value="FULL" readOnly /></label>
        <label>Physics Backend<input value="Jolt Reference (planned)" readOnly /></label>
        <div className="note">当前页面是编辑器工程壳。下一阶段接入 WASM Core、参数 Schema、动力链拓扑与可交互试车台。</div>
      </aside>

      <section className="telemetry">
        <div><span>Speed</span><b>0.0 km/h</b></div>
        <div><span>Engine</span><b>0 rpm</b></div>
        <div><span>Gear</span><b>N</b></div>
        <div><span>Track Slip</span><b>0.00</b></div>
        <div><span>Step</span><b>120 Hz</b></div>
      </section>
    </main>
  )
}
