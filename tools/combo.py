import os
import struct
import argparse

def merge_bin_files(input_dir):
    # 获取脚本所在目录
    script_dir = input_dir if input_dir else os.path.dirname(os.path.abspath(__file__))
    
    # 定义文件路径
    fonts_bin_path = os.path.join(script_dir, 'fonts', 'fonts.bin')
    images_bin_path = os.path.join(script_dir, 'images', 'images.bin')
    output_bin_path = os.path.join(script_dir, 'data.bin')
    
    # 读取fonts.bin内容（如果存在）
    fonts_data = b''
    if os.path.exists(fonts_bin_path):
        with open(fonts_bin_path, 'rb') as f:
            fonts_data = f.read()
        print(f"读取 {fonts_bin_path} 成功")
    else:
        print(f"警告: {fonts_bin_path} 文件不存在，将使用空数据")
    
    # 读取images.bin内容（如果存在）
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
    
    print(f"成功合并数据到 {output_bin_path}")

def merge_txt_files(input_dir):
    # 获取脚本所在目录
    script_dir = input_dir if input_dir else os.path.dirname(os.path.abspath(__file__))
    
    # 定义文件路径
    fonts_txt_path = os.path.join(script_dir, 'fonts', 'fonts.txt')
    images_txt_path = os.path.join(script_dir, 'images', 'images.txt')
    output_txt_path = os.path.join(script_dir, 'data.txt')
    
    # 获取fonts.bin的大小，用于计算偏移
    fonts_bin_path = os.path.join(script_dir, 'fonts', 'fonts.bin')
    fonts_bin_size = os.path.getsize(fonts_bin_path) if os.path.exists(fonts_bin_path) else 0
    
    # 读取fonts.txt内容（如果存在）
    fonts_lines = []
    if os.path.exists(fonts_txt_path):
        with open(fonts_txt_path, 'r', encoding='utf-8') as f:
            fonts_lines = f.readlines()
        print(f"读取 {fonts_txt_path} 成功")
    else:
        print(f"警告: {fonts_txt_path} 文件不存在，将使用空数据")
    
    # 读取images.txt内容并处理偏移（如果存在）
    processed_images_lines = []
    if os.path.exists(images_txt_path):
        with open(images_txt_path, 'r', encoding='utf-8') as f:
            images_lines = f.readlines()
        
        # 处理images.txt中的偏移地址
        for line in images_lines:
            if line.strip():
                # 假设每行的格式是 "name:offset ..."
                parts = line.strip().split(':')
                if len(parts) >= 2:
                    # 将偏移地址加上fonts.bin的大小
                    try:
                        # 处理可能包含0x前缀的十六进制数
                        name = parts[0]
                        offset_str = parts[1]
                        if offset_str.startswith('0x') or offset_str.startswith('0X'):
                            offset = int(offset_str, 16)
                        else:
                            offset = int(offset_str, 16)  # 原数据也应是十六进制格式
                        
                        new_offset = offset + fonts_bin_size
                        processed_images_lines.append(f"{name}:0x{new_offset:08X}\n")
                    except ValueError:
                        # 如果不是数字格式，保持原样
                        processed_images_lines.append(line)
                else:
                    processed_images_lines.append(line)
            else:
                processed_images_lines.append(line)
        print(f"读取 {images_txt_path} 成功")
    else:
        print(f"警告: {images_txt_path} 文件不存在，将使用空数据")
    
    # 合并txt文件
    with open(output_txt_path, 'w', encoding='utf-8') as f:
        f.writelines(fonts_lines)
        if processed_images_lines:  # 只有当有图像数据时才添加空行
            f.write('\n')  # 添加空行分隔
        f.writelines(processed_images_lines)
    
    print(f"成功合并数据到 {output_txt_path}")
    print(f"已应用偏移量: 0x{fonts_bin_size:X}")

# 添加清除过程文件的函数
def cleanup_process_files(input_dir):
    # 获取脚本所在目录
    script_dir = input_dir if input_dir else os.path.dirname(os.path.abspath(__file__))
    
    # 定义需要清理的目录
    directories = [
        os.path.join(script_dir, 'fonts'),
        os.path.join(script_dir, 'images')
    ]
    
    # 删除所有.txt和.bin文件
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
    
    print("开始合并文件...")
    
    # 检查fonts和images目录是否存在，但不强制要求都存在
    fonts_dir_exists = os.path.exists(os.path.join(script_dir, 'fonts'))
    images_dir_exists = os.path.exists(os.path.join(script_dir, 'images'))
    
    if not fonts_dir_exists and not images_dir_exists:
        print("错误: fonts 和 images 文件夹都不存在")
        return
    
    if not fonts_dir_exists:
        print("警告: fonts 文件夹不存在")
    
    if not images_dir_exists:
        print("警告: images 文件夹不存在")
    
    # 合并bin文件
    merge_bin_files(input_dir)
    
    # 合并txt文件
    merge_txt_files(input_dir)
    
    # 清除过程文件
    cleanup_process_files(input_dir)
    
    print("文件合并完成!")

if __name__ == "__main__":
    main()

