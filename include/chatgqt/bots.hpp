// ������һЩԤ��� ChatGQT

#pragma once

#include <fstream>
#include <memory>
#include <chatgqt/chatgqt.hpp>

// ���ļ����� Bot
std::unique_ptr<ChatGQT> generateBotFromFile(const std::string& path);
