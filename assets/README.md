# Sample Assets for AssetTools

This directory contains small, text-based sample asset definitions used to
demonstrate and test the AssetTools validation pipeline.

These files represent simplified asset metadata, not real game content.
They are intentionally minimal and deterministic so the tool can be
run immediately after cloning the repository.

## File Format

Each line defines a single asset:

<Type> <Name> <SizeKB>

Example:
Texture PlayerIcon 256

## Files

- valid_assets.txt  
  Assets that pass all validation rules.

- invalid_assets.txt  
  Assets that intentionally violate validation rules to demonstrate
  error reporting and failure behavior.
