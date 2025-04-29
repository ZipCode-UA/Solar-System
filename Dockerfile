# Arch Linux base development package
FROM archlinux:base-devel

# Update distro and install C++ packages
RUN pacman -Syu  --noconfirm \
    lldb \
    git \
    clang \
    ninja \
    cmake \
    && pacman -Scc --noconfirm

# Install raylib dependencies
RUN sudo pacman -S --noconfirm \
    alsa-lib \
    mesa \
    libx11 \
    libxrandr \
    libxi \
    libxcursor \
    libxinerama \
    && pacman -Scc --noconfirm
