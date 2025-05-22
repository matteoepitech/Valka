#!/usr/bin/env nix-shell
#! nix-shell -i bash --pure
#! nix-shell -p llvmPackages_19.libllvm gcc

make fclean
make

# The builder is not working correctly since I can't really try on Docker, (conflict with nix for the moment)
