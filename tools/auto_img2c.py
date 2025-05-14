import os
import yaml
import subprocess
import sys
from PIL import Image
import shutil
def process_image(output_dir, image_path, output_path ,output_name):
    command = [
        sys.executable,
        os.path.join(output_dir, 'img2c.py'),
        '-i', image_path,
        '-o', output_path,
        '--name', output_name
    ]
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

header_content_start = f"""#ifndef __UI_IMAGES_H__
#define __UI_IMAGES_H__

#ifdef __cplusplus
extern "C" {{
#endif

#include "arm_2d.h"
#include "ldConfig.h"
"""

header_content_end = f"""
#ifdef __cplusplus
}}
#endif

#endif
"""

def generate_image_data_for_each_config(imageYaml, output_dir):
    for image_entry in imageYaml:
        image_path = image_entry.get("path")
        if image_path:
            dest_path = os.path.join(output_dir, os.path.basename(image_path))

            os.makedirs(os.path.dirname(dest_path), exist_ok=True)
            shutil.copyfile(image_path, dest_path)
            thisPyDirPath = os.path.dirname(os.path.abspath(__file__))
    print(output_dir)
    print('\nfile list:')
    header_content=""
    for filename in os.listdir(output_dir):
        if filename.lower().endswith(('.png', '.jpg', '.jpeg', '.gif', '.bmp')):
            base_name, file_extension = os.path.splitext(filename)
            image_path = os.path.join(output_dir, filename)
            new_filename = f"{base_name}.c"
            output_path = os.path.join(output_dir, new_filename)
            output_name = f'_{filename.replace(".", "_")}_'
            text_file_name=filename.replace(".", "_")
            print('    ',filename,' -> ',text_file_name)
            process_image(thisPyDirPath, image_path, output_path, output_name)
            with Image.open(image_path) as img:
                imgW, imgH = img.size
                header_content += f"""
// {filename} < {imgW}x{imgH} >"""

            header_content += f"""
#if LD_CFG_COLOR_DEPTH == 8
extern const arm_2d_tile_t c_tile_{text_file_name}_GRAY8;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_GRAY8
#elif LD_CFG_COLOR_DEPTH == 16
extern const arm_2d_tile_t c_tile_{text_file_name}_RGB565;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_RGB565
#else"""
            print(file_extension)
            if(file_extension=='.png' or file_extension=='.gif'):
                header_content += f"""
extern const arm_2d_tile_t c_tile_{text_file_name}_CCCA8888;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_CCCA8888
#endif"""
            else:
                header_content += f"""
extern const arm_2d_tile_t c_tile_{text_file_name}_CCCN888;
#define IMAGE_{text_file_name.upper()}          (arm_2d_tile_t*)&c_tile_{text_file_name}_CCCN888
#endif"""

            if(file_extension=='.png'):
                header_content += f"""
extern const arm_2d_tile_t c_tile_{text_file_name}_A1Mask;
#define IMAGE_{text_file_name.upper()}_A1Mask   (arm_2d_tile_t*)&c_tile_{text_file_name}_A1Mask
extern const arm_2d_tile_t c_tile_{text_file_name}_A2Mask;
#define IMAGE_{text_file_name.upper()}_A2Mask   (arm_2d_tile_t*)&c_tile_{text_file_name}_A2Mask
extern const arm_2d_tile_t c_tile_{text_file_name}_A4Mask;
#define IMAGE_{text_file_name.upper()}_A4Mask   (arm_2d_tile_t*)&c_tile_{text_file_name}_A4Mask
extern const arm_2d_tile_t c_tile_{text_file_name}_Mask;
#define IMAGE_{text_file_name.upper()}_Mask     (arm_2d_tile_t*)&c_tile_{text_file_name}_Mask
"""
            else:
                header_content += f"""
"""

            with open(f"{output_dir}/uiImages.h", 'w') as file:
                file.write(header_content_start)
                file.flush()
                file.write(header_content)
                file.flush()
                file.write(header_content_end)
                file.flush()
            os.remove(image_path)
    print('completed\n')
def main(argv):
    if not argv:
        output_dir = os.path.dirname(os.path.abspath(__file__))
    else:
        output_dir = argv[0]
    if output_dir[-1] == '\\' or output_dir[-1] == '/':
        output_dir = output_dir[:-1]

    image_yaml_path = os.path.join(output_dir, "image.yaml")

    if os.path.exists(image_yaml_path):
        with open(image_yaml_path, 'r') as file:
            imageYamlData = yaml.safe_load(file)
            generate_image_data_for_each_config(imageYamlData, output_dir)
    else:
        print("image.yaml not found")

if __name__ == "__main__":
    main(sys.argv[1:])
