# Use an official C++ build environment
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libsdl2-dev \                
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    && rm -rf /var/lib/apt/lists/*

# Create app directory
WORKDIR /app/build

# Copy source files
COPY . .

# Create build directory
RUN cmake .. && make

# Set the binary as entrypoint
CMD ["./carter"]
