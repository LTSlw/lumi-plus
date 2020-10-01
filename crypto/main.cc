#include <QByteArray>
#include <QString>
#include <fstream>
#include <iostream>
#include <string>

#include "Qt-AES/qaesencryption.h"
using namespace std;

string DecryptFromBase64(const QByteArray& base64_cipher_text,
                         const QString& key) {
  return QAESEncryption::RemovePadding(
             QAESEncryption::Decrypt(
                 QAESEncryption::AES_128, QAESEncryption::CBC,
                 QByteArray::fromBase64(base64_cipher_text), key.toUtf8(),
                 key.toUtf8(), QAESEncryption::PKCS7),
             QAESEncryption::PKCS7)
      .toStdString();
}

string EncryptToBase64(const QString& plain_text, const QString& key) {
  return QAESEncryption::Crypt(QAESEncryption::AES_128, QAESEncryption::CBC,
                               plain_text.toUtf8(), key.toUtf8(), key.toUtf8(),
                               QAESEncryption::PKCS7)
      .toBase64()
      .toStdString();
}

int main(void) {
  if (ifstream text_is{"input.txt", std::ios::binary | std::ios::ate}) {
    auto input_size = text_is.tellg();
    string input(input_size, '\0');
    text_is.seekg(0);
    if (text_is.read(&input[0], input_size)) {
      if (ifstream key_is{"key.txt", std::ios::binary | std::ios::ate}) {
        auto key_size = key_is.tellg();
        string key(key_size, '\0');
        key_is.seekg(0);
        if (key_is.read(&key[0], key_size)) {
          if (ofstream enc_os{"enc_output.txt"}) {
            enc_os << EncryptToBase64(QString::fromStdString(input),
                                      QString::fromStdString(key));
          } else {
            cerr << "Failed to output encryption result!" << endl;
          }

          if (ofstream dec_os{"dec_output.txt"}) {
            dec_os << DecryptFromBase64(
                QByteArray::fromRawData(input.c_str(), input_size),
                QString::fromStdString(key));
          } else {
            cerr << "Failed to output decryption result!" << endl;
          }

        } else {
          cerr << "Failed to read key!" << endl;
        }
      } else {
        cerr << "Failed to open key file!" << endl;
      }
    } else {
      cerr << "Failed to read input!" << endl;
    }
  } else {
    cerr << "Failed to open input file!" << endl;
  }
  return 0;
}
