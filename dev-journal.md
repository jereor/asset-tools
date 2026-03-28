# Dev Journal

## 2026-03-28
- Did: I integrated vcpkg into a Jenkins pipeline running Docker builds. It worked locally, but CI exposed several hidden issues.
- Learned: The challenge wasn’t vcpkg — it was consistency across Docker, Jenkins, and filesystem permissions. Once users, paths, and volumes were aligned, everything worked.
- Stuck on: