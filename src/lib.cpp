#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "pack109.hpp"

//Boolean values
vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE); //True tag
  } else {
    bytes.push_back(PACK109_FALSE); //False tag
  }
  return bytes;
}
bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) {
     throw;
  }
  if (bytes[0] == PACK109_TRUE) { //Check true tag
    return true;
  } else if (bytes[0] == PACK109_FALSE) { //Check false tag
    return false;
  } else {
    throw;
  }

}

//unsigned 8-bit integer
vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8); //u8 tag
  bytes.push_back(item);
  return bytes;
}
u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_U8) { //check u8 tag
    return bytes[1];
  } else {
    throw;
  }
}

//unsigned 32-bit integer
vec pack109::serialize(u32 item) {
  vec bytes;
  int num[4];
  //separates item tnto bytes
  num[0] = (item >> 24) & 0xFF;
  num[1] = (item >> 16) & 0xFF;
  num[2] = (item >> 8) & 0xFF; 
  num[3] = item & 0xFF; 
  bytes.push_back(PACK109_U32); //u32 tag
  for(int i = 0; i < 4; i++){
    bytes.push_back(num[i]);
  }
  return bytes;
}
u32 pack109::deserialize_u32(vec bytes) {
  if (bytes.size() < 5) {
    throw;
  }
  if (bytes[0] == PACK109_U32) {//check u32 tag
    //concantenates bytes
    u32 ret_num = (bytes[1] << 24) | (bytes[2] << 16) | (bytes[3] << 8) | (bytes[4]);
    return ret_num;
  } else {
    throw;
  }
}

//unsigned 64-bit integer
vec pack109::serialize(u64 item) {
  vec bytes;
  int num[8];
  //separates item into bytes
  num[0] = (item >> 56) & 0xFF;
  num[1] = (item >> 48) & 0xFF;
  num[2] = (item >> 40) & 0xFF; 
  num[3] = (item >> 32) & 0xFF; 
  num[4] = (item >> 24) & 0xFF;
  num[5] = (item >> 16) & 0xFF;
  num[6] = (item >> 8) & 0xFF; 
  num[7] = item & 0xFF; 
  bytes.push_back(PACK109_U64);//u64 tag
  for(int i = 0; i < 8; i++){
    bytes.push_back(num[i]);
  }
  return bytes;
}
u64 pack109::deserialize_u64(vec bytes) {
  if (bytes.size() < 9) {
    throw;
  }
  if (bytes[0] == PACK109_U64) {//check u64 tag
    //organizes bytes
    u64 byte1 = bytes[1];
    byte1 = byte1 << 56;
    u64 byte2 = bytes[2];
    byte2 = byte2 << 48;
    u64 byte3 = bytes[3];
    byte3 = byte3 << 40;
    u64 byte4 = bytes[4];
    byte4 = byte4 << 32;
    u64 byte5 = bytes[5];
    byte5 = byte5 << 24;
    u64 byte6 = bytes[6];
    byte6 = byte6 << 16;
    u64 byte7 = bytes[7];
    byte7 = byte7 << 8;
    u64 byte8 = bytes[8];
    //concantenates bytes
    u64 ret_num = (byte1) + (byte2) + (byte3) + (byte4) + (byte5) + (byte6) + (byte7) + (byte8);
    return ret_num;
  } else {
    throw;
  }
}

//signed 8-bit integer
vec pack109::serialize(i8 item) {
  vec bytes;
  bytes.push_back(PACK109_I8);//i8 tag
  bytes.push_back(item);
  return bytes;
}
i8 pack109::deserialize_i8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_I8) {//checks i8 tag
    return bytes[1];
  } else {
    throw;
  }
}

//signed 32-bit integer
vec pack109::serialize(i32 item) {
  vec bytes;
  int num[4];
  //splits bytes
  num[0] = (item >> 24) & 0xFF;
  num[1] = (item >> 16) & 0xFF;
  num[2] = (item >> 8) & 0xFF; 
  num[3] = item & 0xFF; 
  bytes.push_back(PACK109_I32);//i32 tag
  for(int i = 0; i < 4; i++){
    bytes.push_back(num[i]);//adds each byte
  }
  return bytes;
}
i32 pack109::deserialize_i32(vec bytes) {
  if (bytes.size() < 5) {
    throw;
  }
  if (bytes[0] == PACK109_I32) {//checks i32 tag
    i32 ret_num = (bytes[1] << 24) | (bytes[2] << 16) | (bytes[3] << 8) | (bytes[4]);//concantenates bytes
    return ret_num;
  } else {
    throw;
  }
}

//signed 64-bit integer
vec pack109::serialize(i64 item) {
  vec bytes;
  int num[8];
  //splits bytes
  num[0] = (item >> 56) & 0xFF;
  num[1] = (item >> 48) & 0xFF;
  num[2] = (item >> 40) & 0xFF; 
  num[3] = (item >> 32) & 0xFF; 
  num[4] = (item >> 24) & 0xFF;
  num[5] = (item >> 16) & 0xFF;
  num[6] = (item >> 8) & 0xFF; 
  num[7] = item & 0xFF; 
  bytes.push_back(PACK109_I64);//adds i64 tag
  for(int i = 0; i < 8; i++){
    bytes.push_back(num[i]);//adds each byte 
  }
  return bytes;
}
i64 pack109::deserialize_i64(vec bytes) {
  if (bytes.size() < 9) {
    throw;
  }
  if (bytes[0] == PACK109_I64) {//checks tag
    //organizes bytes
    i64 byte1 = bytes[1];
    byte1 = byte1 << 56;
    i64 byte2 = bytes[2];
    byte2 = byte2 << 48;
    i64 byte3 = bytes[3];
    byte3 = byte3 << 40;
    i64 byte4 = bytes[4];
    byte4 = byte4 << 32;
    i64 byte5 = bytes[5];
    byte5 = byte5 << 24;
    i64 byte6 = bytes[6];
    byte6 = byte6 << 16;
    i64 byte7 = bytes[7];
    byte7 = byte7 << 8;
    i64 byte8 = bytes[8];
    //concantenates bytes
    i64 ret_num = (byte1) + (byte2) + (byte3) + (byte4) + (byte5) + (byte6) + (byte7) + (byte8);
    return ret_num;
  } else {
    throw;
  }
}

//32-bit float
vec pack109::serialize(f32 item) {
  vec bytes;
  bytes.push_back(PACK109_F32);//adds f32 tag
  u32 u32_item = *(reinterpret_cast<u32*>(&item));
  //adds each byte
  bytes.push_back(u32_item >> 24);
  bytes.push_back(u32_item >> 16);
  bytes.push_back(u32_item >> 8);
  bytes.push_back(u32_item);
  return bytes;
}
f32 pack109::deserialize_f32(vec bytes) {
  if (bytes.size() < 5) {
    throw;
  }
  if (bytes[0] == PACK109_F32) {// checks tag
    //concantenates bytes
    u32 u32_num = (static_cast<u32>(bytes[1]) << 24) | (static_cast<u32>(bytes[2]) << 16) | (static_cast<u32>(bytes[3]) << 8) | (static_cast<u32>(bytes[4]));
    f32 ret_num = *(reinterpret_cast<f32*>(&u32_num));
    return ret_num;
  } else {
    throw;
  }
}

//64-bit float
vec pack109::serialize(f64 item) {
  vec bytes;
  bytes.push_back(PACK109_F64);//adds f64 flag
  u64 u64_item = *(reinterpret_cast<u64*>(&item));
  //adds each byte
  bytes.push_back(u64_item >> 56);
  bytes.push_back(u64_item >> 48);
  bytes.push_back(u64_item >> 40);
  bytes.push_back(u64_item >> 32);
  bytes.push_back(u64_item >> 24);
  bytes.push_back(u64_item >> 16);
  bytes.push_back(u64_item >> 8);
  bytes.push_back(u64_item);
  return bytes;
}
f64 pack109::deserialize_f64(vec bytes) {
  if (bytes.size() < 9) {
    throw;
  }
  if (bytes[0] == PACK109_F64) {//checks flag
    //concantenates bytes
    u64 u64_num = (static_cast<u64>(bytes[1]) << 56) | (static_cast<u64>(bytes[2]) << 48) | (static_cast<u64>(bytes[3]) << 40) | (static_cast<u64>(bytes[4]) << 32)| (static_cast<u64>(bytes[5]) << 24) | (static_cast<u64>(bytes[6]) << 16) | (static_cast<u64>(bytes[7]) << 8) | (static_cast<u64>(bytes[8]));
    f64 ret_num = *(reinterpret_cast<f64*>(&u64_num));
    return ret_num;
  } else {
    throw;
  }
}

//strings
vec pack109::serialize(string item) {
  vec bytes;
  if(item.size() <= 255){ //s8
    bytes.push_back(PACK109_S8); //adds s8 tag
    bytes.push_back(item.size());//adds string size
    for(int i = 0; i < item.size(); i++){
      bytes.push_back((int)item[i]);//adds each char
    }
  }else{ //s16
    bytes.push_back(PACK109_S16);//adds s16 tag
    bytes.push_back((item.size() >> 8) & 0xFF); //adds first byte of size
    bytes.push_back(item.size() & 0xFF); //adds second byte of size
    for(int i = 0; i < item.size(); i++){
      bytes.push_back((int)item[i]);//adds each char
    }
  }
  return bytes;
}
string pack109::deserialize_string(vec bytes) {
  if (bytes.size() < 3) {
    throw;
  }
  //checks len
  if (bytes[0] == PACK109_S8) {
    string ret_string = "";
    for(int i = 0; i < bytes[1]; i++){
      ret_string += bytes[i+2];//concantenates chars
    }
    return ret_string;
  } else if (bytes[0] == PACK109_S16) {
    string ret_string = "";
    int num_int = (bytes[1] << 8) | (bytes[2]);
    for(int i = 3; i < num_int+3; i++){
      ret_string += bytes[i];//concantenates chars
    }
    return ret_string;
  } else {
    throw;
  }
}

//u8 array
vec pack109::serialize(std::vector<u8> item) {
  vec bytes;
  //checks len
  if(item.size() <= 255){ 
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
    for(int i = 0; i < item.size(); i++){
      bytes.push_back((int)item[i]);//pushes each int
    }
  }else{
    bytes.push_back(PACK109_A16);
    bytes.push_back((item.size() >> 8) & 0xFF); 
    bytes.push_back(item.size() & 0xFF); 
    for(int i = 0; i < item.size(); i++){
      bytes.push_back((int)item[i]);//pushes each int
    }
  }
  return bytes;
}
std::vector<u8> pack109::deserialize_vec_u8(vec bytes){
  std::vector<u8> ret_vec;
  if (bytes.size() < 3) {
    throw;
  }
  if (bytes[0] == PACK109_A8) {
    for(int i = 2; i < bytes[1]+2; i++){
      ret_vec.push_back(bytes[i]);//adds each byte to return vector
    }
    return ret_vec;
  } else if (bytes[0] == PACK109_A16) {
    int num_int = (bytes[1] << 8) | (bytes[2]);
    for(int i = 3; i < num_int; i++){
      ret_vec.push_back(bytes[i]);//adds each byte to return vector
    }
    return ret_vec;
  } else {
    throw;
  }
}

//u64 array
vec pack109::serialize(std::vector<u64> item) {
  vec bytes;
  if(item.size() <= 255){ //checks len
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
    for(int i = 0; i < item.size(); i++){
      vec int_bytes = serialize(item[i]);//calls u64 serialization
      for(int j = 1; j < int_bytes.size(); j++){
        bytes.push_back(int_bytes[j]);
      }
    }
  }else{
    bytes.push_back(PACK109_A16);
    bytes.push_back((item.size() >> 8) & 0xFF); 
    bytes.push_back(item.size() & 0xFF); 
    for(int i = 0; i < item.size(); i++){
      vec int_bytes = serialize(item[i]);//calls u64 serialization
      for(int j = 1; j < int_bytes.size(); j++){
        bytes.push_back(int_bytes[j]);
      }
    }
  }
  return bytes;
}
std::vector<u64> pack109::deserialize_vec_u64(vec bytes){
  std::vector<u64> ret_vec;
  if (bytes.size() < 3) {
    throw;
  }
  if (bytes[0] == PACK109_A8) {
    for(int i = 2; i < bytes[1]*8; i+=8){
      u64 byte1 = bytes[0+i];
      byte1 = byte1 << 56;
      u64 byte2 = bytes[1+i];
      byte2 = byte2 << 48;
      u64 byte3 = bytes[2+i];
      byte3 = byte3 << 40;
      u64 byte4 = bytes[3+i];
      byte4 = byte4 << 32;
      u64 byte5 = bytes[4+i];
      byte5 = byte5 << 24;
      u64 byte6 = bytes[5+i];
      byte6 = byte6 << 16;
      u64 byte7 = bytes[6+i];
      byte7 = byte7 << 8;
      u64 byte8 = bytes[7+i];
      u64 element = (byte1) + (byte2) + (byte3) + (byte4) + (byte5) + (byte6) + (byte7) + (byte8);//concantenates bytes of each u64
      ret_vec.push_back(element);
    }
    return ret_vec;
  } else if (bytes[0] == PACK109_A16) {
    int num_int = (bytes[1] << 8) | (bytes[2]);//adds len bytes
    for(int i = 3; i < num_int*8; i+=8){
      u64 byte1 = bytes[0+i];
      byte1 = byte1 << 56;
      u64 byte2 = bytes[1+i];
      byte2 = byte2 << 48;
      u64 byte3 = bytes[2+i];
      byte3 = byte3 << 40;
      u64 byte4 = bytes[3+i];
      byte4 = byte4 << 32;
      u64 byte5 = bytes[4+i];
      byte5 = byte5 << 24;
      u64 byte6 = bytes[5+i];
      byte6 = byte6 << 16;
      u64 byte7 = bytes[6+i];
      byte7 = byte7 << 8;
      u64 byte8 = bytes[7+i];
      u64 element = (byte1) + (byte2) + (byte3) + (byte4) + (byte5) + (byte6) + (byte7) + (byte8);//concantenates bytes of each u64
      ret_vec.push_back(element);
    }
    return ret_vec;
  } else {
    throw;
  }
}

//f64 array
vec pack109::serialize(std::vector<f64> item) {
  vec bytes;
  if(item.size() <= 255){ //checks len
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
    for(int i = 0; i < item.size(); i++){
      vec int_bytes = serialize(item[i]);
      for(int j = 1; j < int_bytes.size(); j++){
        bytes.push_back(int_bytes[j]);
      }
    }
  }else{
    bytes.push_back(PACK109_A16);
    bytes.push_back((item.size() >> 8) & 0xFF); 
    bytes.push_back(item.size() & 0xFF); //added each size byte
    for(int i = 0; i < item.size(); i++){
      vec int_bytes = serialize(item[i]);
      for(int j = 1; j < int_bytes.size(); j++){
        bytes.push_back(int_bytes[j]);
      }
    }
  }
  return bytes;
}
std::vector<f64> pack109::deserialize_vec_f64(vec bytes){
  std::vector<f64> ret_vec;
  if (bytes.size() < 3) {
    throw;
  }
  if (bytes[0] == PACK109_A8) {
    for(int i = 2; i < bytes[1]*8; i+=8){
      //concantenates each byte of the elements
      u64 u64_num = (static_cast<u64>(bytes[i]) << 56) | (static_cast<u64>(bytes[1+i]) << 48) | (static_cast<u64>(bytes[2+i]) << 40) | (static_cast<u64>(bytes[3+i]) << 32)| (static_cast<u64>(bytes[4+i]) << 24) | (static_cast<u64>(bytes[5+i]) << 16) | (static_cast<u64>(bytes[6+i]) << 8) | (static_cast<u64>(bytes[7+i]));
      f64 element = *(reinterpret_cast<f64*>(&u64_num));
      ret_vec.push_back(element);
    }
    return ret_vec;
  } else if (bytes[0] == PACK109_A16) {
    int num_int = (bytes[1] << 8) | (bytes[2]);//adds len bytes
    for(int i = 3; i < num_int*8; i+=8){
      //concantenates each byte of the elements
      u64 u64_num = (static_cast<u64>(bytes[i]) << 56) | (static_cast<u64>(bytes[1+i]) << 48) | (static_cast<u64>(bytes[2+i]) << 40) | (static_cast<u64>(bytes[3+i]) << 32)| (static_cast<u64>(bytes[4+i]) << 24) | (static_cast<u64>(bytes[5+i]) << 16) | (static_cast<u64>(bytes[6+i]) << 8) | (static_cast<u64>(bytes[7+i]));
      f64 element = *(reinterpret_cast<f64*>(&u64_num));
      ret_vec.push_back(element);
    }
    return ret_vec;
  } else {
    throw;
  }
}

vec pack109::serialize(std::vector<string> item){
  vec bytes;
  if(item.size() <= 255){ //checks len of array
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
    for(int i = 0; i < item.size(); i++){
      if(item[i].size() <= 255){ //checks len of string
        bytes.push_back(PACK109_S8);
        bytes.push_back(item[i].size());
        for(int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]);
        }
      }else{
        bytes.push_back(PACK109_S16);
        bytes.push_back((item[i].size() >> 8) & 0xFF); 
        bytes.push_back(item[i].size() & 0xFF); 
        for(int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]);
        }
      }
    }
  }else{
    bytes.push_back(PACK109_A16);
    bytes.push_back((item.size() >> 8) & 0xFF); 
    bytes.push_back(item.size() & 0xFF); //adds len bytes
    for(int i = 0; i < item.size(); i++){
      if(item[i].size() <= 255){//checks string len
        bytes.push_back(PACK109_S8);
        bytes.push_back(item[i].size());
        for(int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]);
        }
      }else{
        bytes.push_back(PACK109_S16);
        bytes.push_back((item[i].size() >> 8) & 0xFF); 
        bytes.push_back(item[i].size() & 0xFF); 
        for(int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]);
        }
      }
    }
  }
  return bytes;
}
std::vector<string> pack109::deserialize_vec_string(vec bytes){
  std::vector<string> ret_vec;
  if (bytes.size() < 3) {
    throw;
  }
  if (bytes[0] == PACK109_A8) {//checks tag
    int i = 2;
    while(i < bytes[1]+2){
      string element = "";
      if(bytes[i] == PACK109_S8){//checks str len
        for(int j = 2; j < (bytes[i+1]+2); j++){
          element += bytes[i+j];
        }
        i += bytes[i+1];
      }else{
        int len = (bytes[i+1] << 8) | (bytes[i+2]);
        for(int j = 2; j < len+2; j++){
          element += bytes[i+j];
        }
        i += len;
      }
      ret_vec.push_back(element);
    }
    return ret_vec;
  } else if (bytes[0] == PACK109_A16) {
    int len = (bytes[1] << 8) | (bytes[2]);
    int i = 2;
    while(i < len+2){
      string element = "";
      if(bytes[i] == PACK109_S8){//checks str len
        for(int j = 2; j < (bytes[i+1]+2); j++){
          element += bytes[i+j];
        }
        i += bytes[i+1];
      }else{
        int len = (bytes[i+1] << 8) | (bytes[i+2]);
        for(int j = 2; j < len+2; j++){
          element += bytes[i+j];
        }
        i += len;
      }
      ret_vec.push_back(element);
    }
    return ret_vec;
  } else {
    throw;
  }
}

vec pack109::serialize(struct Person item){
  vec bytes;
  if(sizeof(item) <= 40){//checks number of elements in struct
    //adds map tag
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x01);
    //identifies type of struct
    bytes.push_back(PACK109_S8);
    string type = "Person";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    //identifies number of elements
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x03);
    //identifies age element
    bytes.push_back(PACK109_S8);
    type = "age";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    //adds age
    bytes.push_back(PACK109_U8);
    bytes.push_back(item.age);
    //identifies height element
    bytes.push_back(PACK109_S8);
    type = "height";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    //adds height
    bytes.push_back(PACK109_F32);
    u32 u32_item = *(reinterpret_cast<u32*>(&item.height));
    bytes.push_back(u32_item >> 24);
    bytes.push_back(u32_item >> 16);
    bytes.push_back(u32_item >> 8);
    bytes.push_back(u32_item);
    //identifies name element
    bytes.push_back(PACK109_S8);
    type = "name";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    string item_name = item.name;
    //adds name
    if((item_name).size() <= 255){
      bytes.push_back(PACK109_S8);
      bytes.push_back((item_name).size());
      for(int k = 0; k < item_name.size(); k++){
        bytes.push_back(item_name[k]);
      }
    }else{
      bytes.push_back(PACK109_S16);
      bytes.push_back((item_name).size());
      for(int k = 0; k < item_name.size(); k++){
        bytes.push_back(item_name[k]);
      }
    }
  }else{
    //adds map tag
    bytes.push_back(PACK109_M16);
    bytes.push_back(0x01);
    //identifies person element
    bytes.push_back(PACK109_S8);
    string type = "Person";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x03);
    //identifies age element
    bytes.push_back(PACK109_S8);
    type = "age";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    //adds age
    bytes.push_back(PACK109_U8);
    bytes.push_back(item.age);
    //identifies height element 
    bytes.push_back(PACK109_S8);
    type = "height";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    //adds height
    bytes.push_back(PACK109_F32);
    u32 u32_item = *(reinterpret_cast<u32*>(&item.height));
    bytes.push_back(u32_item >> 24);
    bytes.push_back(u32_item >> 16);
    bytes.push_back(u32_item >> 8);
    bytes.push_back(u32_item);
    //identifies name element
    bytes.push_back(PACK109_S8);
    type = "name";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    string item_name = item.name;
    //adds name
    if((item_name).size() <= 255){
      bytes.push_back(PACK109_S8);
      bytes.push_back((item_name).size());
      for(int k = 0; k < item_name.size(); k++){
        bytes.push_back(item_name[k]);
      }
    }else{
      bytes.push_back(PACK109_S16);
      bytes.push_back((item_name).size());
      for(int k = 0; k < item_name.size(); k++){
        bytes.push_back(item_name[k]);
      }
    }
  }
  return bytes;
}

struct Person pack109::deserialize_person(vec bytes){
  Person p;
  int element = 0;
  if(bytes.size() < 15){
    throw;
  }
  //checks map tag
  if(bytes[element] == PACK109_M8){
    element+=2;
    //checks for person struct
    if(bytes[element] == PACK109_S8){
      string ret_string = "";
      int name_len = bytes[3];
      for(int i = 0; i < name_len; i++){
        ret_string += bytes[i+4];
      }
      element += name_len+2;
      if(bytes[element] == PACK109_M8){
        element += 3;
        element += bytes[element]+1;
        //checks age
        if (bytes[element] == PACK109_U8) {
          p.age = bytes[element+1];
          element += 3;
          element += bytes[element]+1;
          //checks height
          if (bytes[element] == PACK109_F32) {
            u32 u32_num = (static_cast<u32>(bytes[element+1]) << 24) | (static_cast<u32>(bytes[element+2]) << 16) | (static_cast<u32>(bytes[element+3]) << 8) | (static_cast<u32>(bytes[element+4]));
            f32 ret_num = *(reinterpret_cast<f32*>(&u32_num));
            p.height = ret_num;
            element += 6;
            element += bytes[element]+1;
            //checks name
            if(bytes[element] == PACK109_S8){
              element += 1;
              string concat_name = "";
              for(int c = 1; c <= bytes[element]; c++){
                concat_name += bytes[element+c];
              }
              p.name = concat_name;
            }else if(bytes[element] == PACK109_S16){
              string concat_name = "";
              for(int c = 1; c <= bytes[element]; c++){
                concat_name += bytes[element+c];
              }
              p.name = concat_name;
            }else{
              throw;
            }
          }
        } else {
          throw;
        }
      }else{
        throw;
      }
    }else{
      throw;
    }
  }else if(bytes[0] == PACK109_M16){
    element+=2;
    if(bytes[element] == PACK109_S8){
      string ret_string = "";
      int name_len = bytes[3];
      for(int i = 0; i < name_len; i++){
        ret_string += bytes[i+4];
      }
      element += name_len+2;
      if(bytes[element] == PACK109_M8){
        element += 3;
        element += bytes[element]+1;
        //checks age
        if (bytes[element] == PACK109_U8) {
          p.age = bytes[element+1];
          element += 3;
          element += bytes[element]+1;
          //checks height
          if (bytes[element] == PACK109_F32) {
            u32 u32_num = (static_cast<u32>(bytes[element+1]) << 24) | (static_cast<u32>(bytes[element+2]) << 16) | (static_cast<u32>(bytes[element+3]) << 8) | (static_cast<u32>(bytes[element+4]));
            f32 ret_num = *(reinterpret_cast<f32*>(&u32_num));
            p.height = ret_num;
            element += 6;
            element += bytes[element]+1;
            //checks name
            if(bytes[element] == PACK109_S8){
              element += 1;
              string concat_name = "";
              for(int c = 1; c <= bytes[element]; c++){
                concat_name += bytes[element+c];
              }
              p.name = concat_name;
            }else if(bytes[element] == PACK109_S16){
              string concat_name = "";
              for(int c = 1; c <= bytes[element]; c++){
                concat_name += bytes[element+c];
              }
              p.name = concat_name;
            }else{
              throw;
            }
          }
        } else {
          throw;
        }
      }else{
        throw;
      }
    }else{
      throw;
    }
  }else{
    throw;
  }
  return p;
}

void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}