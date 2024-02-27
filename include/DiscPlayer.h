/*
 * @Author: spongearale
 * @Date: 2024-02-27 21:03:18
 * @LastEditors: spongearale
 * @LastEditTime: 2024-02-27 21:03:19
 * @FilePath: /LeptSound/include/DiscPlayer.h
 * @Description:
 *
 * @Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#ifndef DISCPLAYER_H
#define DISCPLAYER_H
class DiscPlayer {
 public:
  virtual void Play() = 0;
  virtual void Stop() = 0;

 protected:
  DiscPlayer(/* args */);
  virtual ~DiscPlayer();
};

#endif  // DISCPLAYER_H
