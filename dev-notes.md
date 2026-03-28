# Dev Notes

## 2026-03-28

### What I'm working on
- Fixing vcpkg permission issues
- Adding vcpkg caching

### Thoughts / ideas
- Docker build user ≠ runtime user -> align UID/GID with arguments
- Jenkins does not run as root user, has UID 1000
- CMake caches aggressively -> clean build/ if issues arise

### Bugs / issues
- vcpkg installed as root, build ran as ubuntu → couldn’t write lock files
- /vcpkg-cache wasn’t mounted into the build container
- CMake kept using /opt/vcpkg from old cache
- $(id -u) doesn’t work in Groovy -> evaluate using sh first, then pass the result

### Links / resources
- 

### Random notes
- CMake caches aggressively → clean build/ if issues arise
- Docker build user ≠ runtime user
