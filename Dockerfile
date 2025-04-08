FROM gcc:9.5.0-bullseye

RUN apt update && apt upgrade -y

RUN apt install -y \
    traceroute \
    man \
    make

CMD ["/bin/bash"]