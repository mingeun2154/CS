# 개발환경 구축

> M1 macOS에서 진행

## Contents		
* ### [OpenGL과 GLU](#)      
* ### [glfw이란 무엇인가](#)
* ### [glfw 다운](#)
* ### [빌드](#)

#    

## OpenGL and GLU
2D, 3D vector graphics를 **렌더링**하기 위한 corss-language, cross-platform API이다.

오직 렌더링만을 위한 API이기 때문에 I/O에 대해서는 지원하지 않는다. 화면을 띄우거나, 키보드나 마우스로부터 입력을 받을 수 있는 함수는 지원하지 않는다.

대부분의 요즘 OS에 기본적으로 설치되어 따로 설치할 필요는 없다.

## glfw
OpenGL을 위한 오픈 소스 라이브러리이다. **context**를 관리하고, **창을 띄우고, 입력을 받고 이벤트를 처리**하는 API를 지원한다.

> context란 window(하나의 창)에 대한 상태 정보들이다.

직접 설치해야한다.

## install glfw

`$ arch -arm64 brew install`

## build
[Makefile](#)을 사용해 빌드했다.

```Makefile
CC = g++

# glfw header file search path
INC = -I/opt/homebrew/Cellar/glfw/3.3.8/include 
# .dylib path (glfw dynamic library version)
LIBS = -L/opt/homebrew/Cellar/glfw/3.3.8/lib
FRAMEWORK = -framework OpenGL

OBJS = p01_prep.o glSetup.o
SRCS = p01_prep.cpp glSetup.cpp

# executable file name
TARGET = p01_prep

$(TARGET) : $(OBJS)
	$(CC) $(LIBS) -o $(TARGET) $(OBJS) $(FRAMEWORK) -lglfw

p01_prep.o : p01_prep.cpp
	$(CC) -c p01_prep.cpp $(INC)

glSetup.o : glSetup.cpp
	$(CC) -c glSetup.cpp $(INC)

clean : 
	rm -rf $(OBJS)
```

* `INC` : glfw 헤더파일을 찾을 수 있는 경로
	> system header search path에 포함되지 않은 헤더파일의 경로는 직접 알려줘야 한다.

* `LIBS` : 프로그램이 런타임에(동적으로) 참조하게 되는 오브젝트 파일
	> macOS에서는 \*.dylib 형태이다. mach object file이라고 한다.

* `FRAMEWORK` : OpenGL framework을 사용함을 알려준다.
	> OpenGL은 시스템 경로에 포함되어 있기 때문에 따로 경로를 알려줄 필요는 없다.
