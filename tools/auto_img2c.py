import os
import yaml
import subprocess
import sys
from PIL import Image
import shutil

def process_image(output_dir, image_path, output_path, output_name, has_alpha):

    command = [
        sys.executable,
        os.path.join(output_dir, 'img2c.py'),
        '-i', image_path,
        '-o', output_path,
        '--name', output_name,
        '--format', 'all'
    ]

    if has_alpha:
        command += ['--a1', '--a2', '--a4']

    try:
        result = subprocess.run(
            command,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        print(result.stdout)
        if result.stderr:
            print(f"Error: {result.stderr}")
    except subprocess.CalledProcessError as e:
        print(f"Error occurred while processing {image_path}: {e.output}")

header_content_start = """#ifndef __UI_IMAGES_H__
#define __UI_IMAGES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_2d.h"
#include "ldConfig.h"
"""

header_content_end = """
#ifdef __cplusplus
}
#endif

#endif
"""

def generate_image_data_for_each_config(imageYaml, output_dir):
    header_parts = []
    
    for image_entry in imageYaml:
        image_path = image_entry.get("path")
        if image_path:
            dest_path = os.path.join(output_dir, os.path.basename(image_path))
            if dest_path != image_path:
                os.makedirs(os.path.dirname(dest_path), exist_ok=True)
                shutil.copyfile(image_path, dest_path)

    print(output_dir)
    print('\nfile list:')

    thisPyDirPath = os.path.dirname(os.path.abspath(__file__))

    for filename in os.listdir(output_dir):
        if filename.lower().endswith(('.png', '.jpg', '.jpeg', '.gif', '.bmp')):
            base_name, _ = os.path.splitext(filename)
            image_path = os.path.join(output_dir, filename)
            output_name = f'_{filename.replace(".", "_")}_'
            text_file_name = filename.replace(".", "_")
            print('    ', filename, ' -> ', text_file_name)

            with Image.open(image_path) as img:
                imgW, imgH = img.size
                has_alpha = img.mode == 'RGBA'

            new_filename = f"{base_name}.c"
            output_path = os.path.join(output_dir, new_filename)
            process_image(thisPyDirPath, image_path, output_path, output_name, has_alpha)

            header_parts.append(f"\n// {filename} < {imgW}x{imgH} >")

            header_parts.append(f"""
#if LD_CFG_COLOR_DEPTH == 8
extern const arm_2d_tile_t c_tile_{text_file_name}_GRAY8;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_GRAY8
#elif LD_CFG_COLOR_DEPTH == 16
extern const arm_2d_tile_t c_tile_{text_file_name}_RGB565;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_RGB565
#else""")

            if has_alpha:
                header_parts.append(f"""
extern const arm_2d_tile_t c_tile_{text_file_name}_CCCA8888;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_CCCA8888
#endif""")
            else:
                header_parts.append(f"""
extern const arm_2d_tile_t c_tile_{text_file_name}_CCCN888;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_CCCN888
#endif""")

            if has_alpha:
                header_parts.append(f"""
extern const arm_2d_tile_t c_tile_{text_file_name}_A1Mask;
#define IMAGE_{text_file_name.upper()}_A1_MASK   (arm_2d_tile_t*)&c_tile_{text_file_name}_A1Mask
extern const arm_2d_tile_t c_tile_{text_file_name}_A2Mask;
#define IMAGE_{text_file_name.upper()}_A2_MASK   (arm_2d_tile_t*)&c_tile_{text_file_name}_A2Mask
extern const arm_2d_tile_t c_tile_{text_file_name}_A4Mask;
#define IMAGE_{text_file_name.upper()}_A4_MASK   (arm_2d_tile_t*)&c_tile_{text_file_name}_A4Mask
extern const arm_2d_tile_t c_tile_{text_file_name}_Mask;
#define IMAGE_{text_file_name.upper()}_MASK     (arm_2d_tile_t*)&c_tile_{text_file_name}_Mask""")
            else:
                header_parts.append(f"""
#define IMAGE_{text_file_name.upper()}_MASK     NULL""")
            os.remove(image_path)
            header_parts.append("\n")

    full_header = header_content_start + ''.join(header_parts) + header_content_end
    with open(f"{output_dir}/uiImages.h", 'w') as file:
        file.write(full_header)

    print('completed\n')

def main(argv):
    if not argv:
        output_dir = os.path.dirname(os.path.abspath(__file__))
    else:
        output_dir = argv[0]

    if output_dir[-1] in ('\\', '/'):
        output_dir = output_dir[:-1]

    image_yaml_path = os.path.join(output_dir, "image.yaml")

    if not os.path.exists(image_yaml_path):
        print("image.yaml not found")
        image_entries = []
        for filename in os.listdir(output_dir):
            if filename.lower().endswith(('.png', '.jpg', '.jpeg', '.gif', '.bmp')):
                full_path = os.path.abspath(os.path.join(output_dir, filename))
                image_entries.append({"path": full_path})

        if image_entries:
            with open(image_yaml_path, 'w') as file:
                yaml.safe_dump(image_entries, file)

    with open(image_yaml_path, 'r') as file:
        imageYamlData = yaml.safe_load(file)
        generate_image_data_for_each_config(imageYamlData, output_dir)

if __name__ == "__main__":
    main(sys.argv[1:])
