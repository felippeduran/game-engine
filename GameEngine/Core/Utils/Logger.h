//
//  Logger.h
//  GameEngine
//
//  Created by Felippe Durán on 21/09/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef Logger_h
#define Logger_h

#define Log(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, ##__VA_ARGS__);

#endif /* Logger_h */
