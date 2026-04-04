# Dev Notes

## 2026-04-04

### What I'm working on
- Create Docker Compose file for spinning up dev env

### Thoughts / ideas
- Always remember to test Dockerfile changes on both dev and Jenkins side, if the Dockerfile is used on both
- Avoid using 'docker compose up' for interactive containers - It’s meant for long-running services

### Bugs / issues
- Dev env did not have the jenkins user -> Dockerfile failed to build locally

### Links / resources
- 

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
