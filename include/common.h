/***
 * @Author: spongearale
 * @Date: 2024-03-29 23:51:07
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 15:42:17
 * @FilePath: /LeptSound/include/common.h
 * @Description:
 * @
 * @Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#ifndef COMMON_H
#define COMMON_H
namespace LeptSound {
template <typename T>
class Singleton {
   protected:
    Singleton() = default;
    ~Singleton() = default;

   public:
    Singleton(T&&) = delete;
    Singleton(const T&) = delete;
    void operator=(const T&) = delete;
    void operator=(T&&) = delete;
    static T& Instance() {
        static T t;
        return t;
    }
};
}  // namespace LeptSound

#endif  // COMMON_H
