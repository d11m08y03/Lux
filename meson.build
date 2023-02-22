project('lux', 'cpp',
        default_options: 'default_library=static')

sdl2_dep = dependency('sdl2')
sdl2_img_dep = dependency('sdl2_image')
sdl2_ttf_dep = dependency('sdl2_ttf')

executable('output', 'src/main.cpp', 'src/window.cpp',
           dependencies: [sdl2_dep, sdl2_img_dep, sdl2_ttf_dep])
