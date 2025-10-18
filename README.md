# `iga_iqp` Package
ROS 2 Humble C++ package

A package 2 node-ból áll: `/gps_publisher_node` és `/path_visualizer_node`.\
A `/gps_publisher_node`-ban statikusan létrejön 5 pont. Ezek 2D-s koordinátáknak felelnek meg. Ezt az 5 pontot hirdeti 1Hz-el a `geometry_msgs/gps_points` topicban.
Erre a topicra iratkozik fel a `/path_visualizer_node` és kezeli a beérkező pont koordinátákat, majd elkezdi hirdetni a `visualization_marker` topicot, amin az RViz2 figyel.
Továbbá a `/path_visualizer_node` figyel arra, hogy ha újra [0, 0] koordináta érkezik, akkor törölje az eddig kirajzolt pályát és előlről kezdje a kirajzolást.

# ROS2 RQT graph:
<img width="1842" height="153" alt="image" src="https://github.com/user-attachments/assets/7389eca7-1860-4248-9d10-69f9eaa4f590" />

# Package and build
Akapértelmezett workspace: `~/ros2_ws/`

## Clone
```bash
cd ~/ros2_ws/src
```
```bash
git clone https://github.com/IgaliMarcell/iga_iqp.git
```

## Build ROS 2 packages
```bash
cd ~/ros2_ws/
```
```bash
colcon build --packages-select iga_iqp --symlink-install
```
### Source
```bash
source ~/ros2_ws/install/setup.bash
```
### Run
```bash
ros2 launch iga_iqp gps_path_visualizer.launch.py
```
## Manuális RViz, ha esetleg probléma lenne
```bash
rviz2
```
### Programon bellül:
- Add Marker-> topic = /visualization_marker
- Fixed frame = map
# RViz-en bellüli illusztráció (Kék pontot tesz a koordináták helyére és zöld vonallal köti össze az egymás utániakat)
<img width="800" height="591" alt="image" src="https://github.com/user-attachments/assets/0831aa56-fdda-4128-8aed-a3d560a46cb3" />

# Indulás után a konzolra logolja, ha elfogynak a pontok: "No more Points!"és újrakezdi a folyamatot: "New cycle detected, clearing path."
<img width="838" height="257" alt="image" src="https://github.com/user-attachments/assets/4cfad692-da05-46d9-b5f5-282fd41725ec" />
