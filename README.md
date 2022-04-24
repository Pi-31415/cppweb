# Requirements

- Docker
- Heroku CLI
- Xcode command line tools

# I . Steps for Development on Host

## 1. Creating Dockerfile

- First create the docker file, in the folder cppbox, with the content

```
FROM gcc:7.3.0
RUN apt-get -qq update
RUN apt-get -qq upgrade
RUN apt-get -qq install cmake
RUN apt-get -qq install libboost-all-dev=1.62.0.1
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
    ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
```

- **Resist the urge to pull from the latest version** of gcc compiler
- -qq installs quietly

## 2. Building Dockerfile

- Then, enter the cppbox directory, and build dockerfile using the following

```
docker build -t cppbox .
```

**IMPORTANT**: Make sure that docker daemon is running.

## 3. Working in dockerfile

- Once the dockerfile is built, get into the docker container using

```
docker run -ti cppbox:latest bash
```

- Check if required libraries are installed (e.g. libboost)

```
find /usr -name libboost*.*
```

Once you see dozens of libboost files, the install is successful.

- To exit container, type

```
exit
```

## 4. Add Volume

Volumes are added to share access between the host machine and the docker container.

To create volume, use

```
docker run -v /Users/pi/Desktop/cppweb:/usr/src/cppweb -ti cppbox:latest bash
```

- Then get into the cppbox directory.

```
cd /usr/src/cppweb
```

- To create a file in the container, use

```
touch MY_FILE.txt
```

## 5. Install Crow

Go to [Crow Project's Github](https://github.com/ipkn/crow), and download the header file.

## 6. Now create a new project (Actually begin working)

Use

```
mkdir hello_crow
cd hello_crow
cp ../crow_all.h .
```

## 7. Build Crow (and the app)

Create a new file and CMakeLists

```
touch main.cpp
touch CMakeLists.txt
```

Then, in the project directory "hello_crow" in this case, create a build file. Then, build the app with

```
cd build
cmake ..
```

Once makefile is generated, **wile in build directory**, compile the app using

```
make
```

## 8. Access from browser

**IMPORTANT**, to access from local host, we need to open the port from docker. First, exit the current container.

```
exit
```

Then, use

```
docker run -v /Users/pi/Desktop/cppweb:/usr/src/cppweb -p 8080:8080 -e PORT=8080  -ti cppbox:latest /usr/src/cppweb/hello_crow/build/hello_crow

```

Go to [http://localhost:8080/](http://localhost:8080/) on browser to see the effect.

# II . Deployment on Heroku

The steps to deploy the C++ web server on heroku are

- Containerize the app
- Heroku login
- Create Heroku App
- Push the container and release it
- Test in browser

## 1. Containerize the app

Run the latest working version

```
docker run -ti cppbox:latest bash
```

Then, open another terminal tab, **go to cppweb directory**, and

```
docker ps
```

to list all the running containers.

Then, copy the container id **(may vary each time, replace the containerID)**

```
docker cp . 8b4dbe4519c6:/usr/src/cppweb
```

Then commit

```
docker commit 8b4dbe4519c6  hello_crow:latest
```

Then, create a new Dockerfile in hello_crow directory, with the content

```
FROM hello_crow
WORKDIR /usr/src/cppweb/hello_crow/build
CMD ["./hello_crow"]
```

## 1. Containerize the app
