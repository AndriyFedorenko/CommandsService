# Commands Service

The Commands Service acceptes commands, executes them and returns the results. The transport for the communication between the client and server is TCP.

## Non Functional requirements

- C++17
- Cmake
- Clion
- Ubuntu

## 3rd Party Dependencies

#### - Libevent  (https://libevent.org/)
		sudo apt update
		sudo apt install libevent-dev

#### - Google Logging Library (https://github.com/google/glog)

##### Building glog with CMake
1. Get the source code and change to it. e.g., cloning with git:
`git clone https://github.com/google/glog.git`
`cd glog`
2. Run CMake to configure the build tree.
`cmake -S . -B build -G "Unix Makefiles"`
3. Afterwards, generated files can be used to compile the project.
`cmake --build build`
4. Test the build software (optional).
`cmake --build build --target test`
5. Install the built files (optional).
`cmake --build build --target install`


## Design

### Brief description

The server receives commands from clients and puts them into a global (thread-safe) queue. Data processor starts N (configurable) threads which are getting commands from the queue and processing them simultaneously.  When data processing is finished, the client writes event is activating and the server sends a response to the client.

### Sequence Diagram

![sd1](https://user-images.githubusercontent.com/10127885/131478811-2d5a3c72-e090-481c-8296-33e867f7dfa6.JPG)

### Class diagrams

#### TcpServer

This class is implementing TCP server.This class is wrapping up libevent functions and implementing asynchronous socket. TCP server is receiving requests, processing requests by DataProcessor and sending responses to clients. The **TcpServer** aggregates **DataProcessor** for processing received commands.

![TcpServer](https://user-images.githubusercontent.com/10127885/131485911-1045ace6-2eab-4477-9cd1-9a32f20bf413.JPG)

#### DataProcessor

This class is processing commands simultaneously. It is using HandlerFactory to handle different commands.

![DataProcesoor](https://user-images.githubusercontent.com/10127885/131489648-25746008-181b-41cd-93cf-25a32df8bb4c.JPG)

### Handlers



## Manual Tesing Results
![ManualTesing](https://user-images.githubusercontent.com/10127885/131414656-6dc55938-c172-4f69-a5ae-f454684eeb63.JPG)

## Requirements

Implement a service (using C++) to accept commands, execute them and return the results. The transport for the communication between the client and server can be TCP or UDP. The client can send multiple commands using the same channel. The service should be able to serve 100's of simultaneous clients. Libevent or epoll usage is assumed. Also any C++ standard library usage compared to boost is preferred. 

The service should be able to run independently. Any 3rd party dependencies should be clearly specified as dependencies in the accompanying README. Please commit your solution into github and provide us with the link to the repository. Please include a README.md which describes the commands and include examples on how to build and run the service. Please also include sample runs with input and the output produced by the service.

Please include enough documentation, within the code, with which we can understand the design choices made and can navigate the code. Consider the coding task as an opportunity to demonstrate your coding style, testing strategy, design skills as well as code organization skills.

Feel free to ask any questions that you might have about the coding task.

Format of the commands is as follows:
<COMMAND> <ARGUMENT 1> <ARGUMENT 2> … <ARGUMENT N>\n

It is assumed that the commands and arguments are separated by spaces and the arguments do not contain spaces.

Response format:
<STATUS> <ANSWER>\n
STATUS - a symbol indicating a result of the command:
"S" - successful
"E" - unsuccessful

A status field and an answer field are separated by a space. The response can contain any number of spaces.

The 3 commands to be supported by the service are as follows:

1. ping 
The response to this command from the backend should be a "pong" message.

E.g. 
$ ping
S pong

$ ping
E Unable to process your request

2. cat [/path/to/filename]
Get the content of the given file

E.g.
$ cat /path/to/filename
S <content of the file>
<content of the file continued>

$ cat /path/to/filename
E File not found.

3. sum [arg1 arg2 arg3 arg4]
Perform a arithmetic sum of given numbers

$ sum [arg1 arg2 arg3 arg4]
S <sum of arg1 + arg2 + arg3>

$ sum 2 b d g
E Invalid argument
