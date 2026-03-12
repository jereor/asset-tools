# Sample Assets for AssetTools

This directory contains small sample assets used to
demonstrate and test the AssetTools pipelines.

These files are NOT production assets.
They are intentionally minimal and deterministic so the tool can be
run immediately after cloning the repository.
All assets are free of licensing restrictions.

## Files for inspection

- sample_texture.png
- sample_sound.wav
- sample_model.fbx

## Files for validation

Each line defines a single asset:
<Type> <Name> <SizeKB>

Example:
Texture PlayerIcon 256

- valid_assets.txt  
  Assets that pass all validation rules.

- invalid_assets.txt  
  Assets that intentionally violate validation rules to demonstrate
  error reporting and failure behavior.
