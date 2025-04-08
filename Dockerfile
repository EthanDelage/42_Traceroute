FROM debian:bookworm

RUN apt update && apt upgrade

RUN apt install -y \
    traceroute \
    man

CMD ["/bin/bash"]