import os
import struct
import argparse

def merge_bin_files(input_dir):
    script_dir = input_dir if input_dir else os.path.dirname(os.path.abspath(__file__))

    fonts_bin_path = os.path.join(script_dir, 'fonts', 'fonts.bin')
    images_bin_path = os.path.join(script_dir, 'images', 'images.bin')
    output_bin_path = os.path.join(script_dir, 'output', 'data.bin')

    fonts_data = b''
    if os.path.exists(fonts_bin_path):
        with open(fonts_bin_path, 'rb') as f:
            fonts_data = f.read()
        print(f"读取 {fonts_bin_path} 成功")
    else:
        print(f"警告: {fonts_bin_path} 文件不存在，将使用空数据")

    images_data = b''
    if os.path.exists(images_bin_path):
        with open(images_bin_path, 'rb') as f:
            images_data = f.read()
        print(f"读取 {images_bin_path} 成功")
    else:
        print(f"警告: {images_bin_path} 文件不存在，将使用空数据")
    
    # 合并bin文件
    with open(output_bin_path, 'wb') as f:
        f.write(fonts_data)
        f.write(images_data)


def merge_txt_files(input_dir):
    script_dir = input_dir if input_dir else os.path.dirname(os.path.abspath(__file__))

    fonts_txt_path = os.path.join(script_dir, 'fonts', 'fonts.txt')
    images_txt_path = os.path.join(script_dir, 'images', 'images.txt')
    output_header_path = os.path.join(script_dir, 'binData.h')

    fonts_bin_path = os.path.join(script_dir, 'fonts', 'fonts.bin')
    fonts_bin_size = os.path.getsize(fonts_bin_path) if os.path.exists(fonts_bin_path) else 0

    fonts_lines = []
    if os.path.exists(fonts_txt_path):
        with open(fonts_txt_path, 'r', encoding='utf-8') as f:
            fonts_lines = f.readlines()
        print(f"读取 {fonts_txt_path} 成功")
    else:
        print(f"警告: {fonts_txt_path} 文件不存在，将使用空数据")

    processed_images_lines = []
    if os.path.exists(images_txt_path):
        with open(images_txt_path, 'r', encoding='utf-8') as f:
            images_lines = f.readlines()

        for line in images_lines:
            if line.strip():
                parts = line.strip().split(':')
                if len(parts) >= 2:
                    try:
                        name = parts[0]
                        offset_str = parts[1]
                        if offset_str.startswith('0x') or offset_str.startswith('0X'):
                            offset = int(offset_str, 16)
                        else:
                            offset = int(offset_str, 16) 
                        
                        new_offset = offset + fonts_bin_size
                        processed_images_lines.append(f"#define {name} (arm_2d_tile_t*)ldBaseGetVresImage(0x{new_offset:08X})\n")
                    except ValueError:
                        processed_images_lines.append(line)
                else:
                    processed_images_lines.append(line)
            else:
                processed_images_lines.append(line)
        print(f"读取 {images_txt_path} 成功")
    else:
        print(f"警告: {images_txt_path} 文件不存在，将使用空数据")

    with open(output_header_path, 'w', encoding='utf-8') as f:
        f.write("#ifndef _DATA_H_\n")
        f.write("#define _DATA_H_\n\n")
        f.write("#include \"arm_2d.h\"\n\n")

        for line in fonts_lines:
            if line.strip():
                parts = line.strip().split(':')
                if len(parts) >= 2:
                    name = parts[0]
                    offset_str = parts[1]
                    if offset_str.startswith('0x') or offset_str.startswith('0X'):
                        offset = int(offset_str, 16)
                    else:
                        offset = int(offset_str, 16)
                    f.write(f"#define {name} (arm_2d_font_t*)ldBaseGetVresFont(0x{offset:08X})\n")

        if processed_images_lines:
            f.write('\n')
        for line in processed_images_lines:
            f.write(line)

        f.write("\n#endif // _DATA_H_\n")




def cleanup_process_files(input_dir):
    script_dir = input_dir if input_dir else os.path.dirname(os.path.abspath(__file__))

    directories = [
        os.path.join(script_dir, 'fonts'),
        os.path.join(script_dir, 'images')
    ]

    for directory in directories:
        if os.path.exists(directory):
            for filename in os.listdir(directory):
                if filename.endswith('.txt') or filename.endswith('.bin'):
                    file_path = os.path.join(directory, filename)
                    try:
                        os.remove(file_path)
                        print(f"已删除: {file_path}")
                    except Exception as e:
                        print(f"删除 {file_path} 失败: {e}")
        else:
            print(f"目录不存在，跳过: {directory}")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('input_dir', nargs='?', default=None, help='输入目录路径')
    args = parser.parse_args()
    input_dir = args.input_dir
    script_dir = input_dir if input_dir else os.path.dirname(os.path.abspath(__file__))

    output_dir = os.path.join(script_dir, 'output')
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    fonts_dir_exists = os.path.exists(os.path.join(script_dir, 'fonts'))
    images_dir_exists = os.path.exists(os.path.join(script_dir, 'images'))
    
    if not fonts_dir_exists and not images_dir_exists:
        print("错误: fonts 和 images 文件夹都不存在")
        return
    
    if not fonts_dir_exists:
        print("警告: fonts 文件夹不存在")
    
    if not images_dir_exists:
        print("警告: images 文件夹不存在")

    merge_bin_files(input_dir)

    merge_txt_files(input_dir)

    cleanup_process_files(input_dir)

if __name__ == "__main__":
    main()

