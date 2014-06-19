Langton
=======

Implementation of Langton's ant (one night coding)

## Help

```bash
-[ HELP ]-
      -d          interactive display off
      -h          this help
      -i <string> use a config file ( cf gold.mpc )
      -o <string> output filename (PNG, JPEG ...)
      -n <int>    number of iteration ( 0 = infinity )
```

## Configuration file example

```python
# Size 
size 512
# Nb states
nbstates 2
# Nb colors
nbcolors 2
# Colors (You need to have a white case)
255 255 255
0 0 0
# Rules
# Format: newColorIndex Rotation newState
# Nota (Rotation) :
# 1 = Forward
# 2 = Right
# 4 = U-Turn
# 8 = Left
# state 0 color 0
1 8 1
# state 0 color 1
1 8 1
# state 1 color 0
1 2 1
# state 1 color 1
0 1 0
```
