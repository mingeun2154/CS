# Socket Programming

> ### references 🔗
윤성우의 열혈 TCP

## Contents		
* ### [socket](#)      
* ### [socket 사용 방법](#)
* ### [example](#)
* ### [socket programming에 사용되는 함수](#)

#    

## socket
socket은 unix 파일이다.

**서로 다른 host에 존재하는 프로세스** 사이의 통신을 위해 사용한다.

unix system의 regular file과 **거의 비슷하게** 다뤄진다.

## How to use
Socket의 사용은 크게 두 가지로 나눌 수 있다. **server**와 **client**이다.

### Server

* socket 생성(open) - `socket()`
* socket 설정 - `setsockopt()`함수 사용. **이 과정은 필수는 아니다**
* socket에 주소 부여 - `bind()`
* socket을 연결 가능상태로 설정 - `listen()`
* 연결 요청 수락 - `accept()`

연결 요청이 수락된 이후에는 `read()`, `write()` 또는 `recv()`, `send()` 함수를 통해 데이터를 송수신 할 수 있다.

이 과정을 통해 생성된 소켓을 **server socket** 또는 **listening socket**이라고 한다.

### Client

* socket 생성(open) - `socket()`
* 연결할 서버에 대한 설정
* 연결 요청 - `connect()`

## Example

코드를 다운받은 뒤 `$ make all` 명령어를 통해 빌드할 수 있다.

[server.c 코드](#)

[client.c 코드](#)

## Useful functions

