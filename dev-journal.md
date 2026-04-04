# Dev Journal

## 2026-04-04
- Did: I Created a Docker Compose file for starting the dev environment in Docker and mounting it to the root of the project as /workspace.
- Learned: Design your Docker setup to be environment-agnostic and purpose-specific. Don’t rely on assumptions from one environment (like a jenkins user existing) — anything your container needs should be explicitly defined so it works the same locally and in CI.
- Stuck on: 

## 2026-03-28
- Did: I integrated vcpkg into a Jenkins pipeline running Docker builds. It worked locally, but CI exposed several hidden issues.
- Learned: The challenge wasn’t vcpkg — it was consistency across Docker, Jenkins, and filesystem permissions. Once users, paths, and volumes were aligned, everything worked.
- Stuck on:
