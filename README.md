# assn4
Computer Graphics Assignment4

main.cpp : main file

Scenegraph.* : Scenegraph의 구조를 구현한 소스파일

ScoreBox.* : score를 display하기 위한 소스파일

Object.* : rendering되는 model들을 위한 소스파일

Background.* : 배경이 되는 직육면체를 위한 소스파일

Plane.* : 배경의 한 면이 되는 Class

PointLight.* : point light를 위한 Class

DirectionalLight.* : directional light를 위한 Class

Character.* :  모델을 위한 소스파일

Camera.* : 카메라 cotrol을 위한 소스파일

shader : vert.glsl -> vertex shader source code
	 frag.glsl -> fragment shader source code

resource :  obj파일을 포함하고 있는 directory

*키 설명 *
w, a, s, d, : 캐릭터 movement
r : 게임 리셋
1 : 1인칭 시점
2 : 3인칭 시점
3 : 맵 전체 시점
4 : texture on and off
5 : gouraud or phong
0 : light on and off
