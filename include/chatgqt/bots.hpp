// 实现从文件读取语料库

#pragma once

#include <fstream>
#include <memory>
#include <chatgqt/chatgqt.hpp>

// 从文件构建 Bot
std::unique_ptr<ChatGQT> generateBotFromFile(const std::string& path);
