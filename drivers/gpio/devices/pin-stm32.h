#pragma once

#define __STM32_PIN(id,GPIOx,PINx) {.pin_id=id,.bank=GPIO##GPIOx,.pin=GPIO_PIN_##PINx}
#define __STM32_PIN_DEFAULT {-1, 0, 0, 0}

#define PINS_STM32F429 \
{                       \
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(1, E, 2),\
    __STM32_PIN(2, E, 3),\
    __STM32_PIN(3, E, 4),\
    __STM32_PIN(4, E, 5),\
    __STM32_PIN(5, E, 6),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(7, I, 8),\
    __STM32_PIN(8, C, 13),\
    __STM32_PIN(9, C, 14),\
    __STM32_PIN(10, C, 15),\
    __STM32_PIN(11, I, 9),\
    __STM32_PIN(12, I, 10),\
    __STM32_PIN(13, I, 11),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(16, F, 0),\
    __STM32_PIN(17, F, 1),\
    __STM32_PIN(18, F, 2),\
    __STM32_PIN(19, F, 3),\
    __STM32_PIN(20, F, 4),\
    __STM32_PIN(21, F, 5),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(24, F, 6),\
    __STM32_PIN(25, F, 7),\
    __STM32_PIN(26, F, 8),\
    __STM32_PIN(27, F, 9),\
    __STM32_PIN(28, F, 10),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(32, C, 0),\
    __STM32_PIN(33, C, 1),\
    __STM32_PIN(34, C, 2),\
    __STM32_PIN(35, C, 3),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(40, A, 0),\
    __STM32_PIN(41, A, 1),\
    __STM32_PIN(42, A, 2),\
    __STM32_PIN(43, H, 2),\
    __STM32_PIN(44, H, 3),\
    __STM32_PIN(45, H, 4),\
    __STM32_PIN(46, H, 5),\
    __STM32_PIN(47, A, 3),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(50, A, 4),\
    __STM32_PIN(51, A, 5),\
    __STM32_PIN(52, A, 6),\
    __STM32_PIN(53, A, 7),\
    __STM32_PIN(54, C, 4),\
    __STM32_PIN(55, C, 5),\
    __STM32_PIN(56, B, 0),\
    __STM32_PIN(57, B, 1),\
    __STM32_PIN(58, B, 2),\
    __STM32_PIN(59, F, 11),\
    __STM32_PIN(60, F, 12),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(63, F, 13),\
    __STM32_PIN(64, F, 14),\
    __STM32_PIN(65, F, 15),\
    __STM32_PIN(66, G, 0),\
    __STM32_PIN(67, G, 1),\
    __STM32_PIN(68, E, 7),\
    __STM32_PIN(69, E, 8),\
    __STM32_PIN(70, E, 9),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(73, E, 10),\
    __STM32_PIN(74, E, 11),\
    __STM32_PIN(75, E, 12),\
    __STM32_PIN(76, E, 13),\
    __STM32_PIN(77, E, 14),\
    __STM32_PIN(78, E, 15),\
    __STM32_PIN(79, B, 10),\
    __STM32_PIN(80, B, 11),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(83, H, 6),\
    __STM32_PIN(84, H, 7),\
    __STM32_PIN(85, H, 8),\
    __STM32_PIN(86, H, 9),\
    __STM32_PIN(87, H, 10),\
    __STM32_PIN(88, H, 11),\
    __STM32_PIN(89, H, 12),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(92, B, 12),\
    __STM32_PIN(93, B, 13),\
    __STM32_PIN(94, B, 14),\
    __STM32_PIN(95, B, 15),\
    __STM32_PIN(96, D, 8),\
    __STM32_PIN(97, D, 9),\
    __STM32_PIN(98, D, 10),\
    __STM32_PIN(99, D, 11),\
    __STM32_PIN(100, D, 12),\
    __STM32_PIN(101, D, 13),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(104, D, 14),\
    __STM32_PIN(105, D, 15),\
    __STM32_PIN(106, G, 2),\
    __STM32_PIN(107, G, 3),\
    __STM32_PIN(108, G, 4),\
    __STM32_PIN(109, G, 5),\
    __STM32_PIN(110, G, 6),\
    __STM32_PIN(111, G, 7),\
    __STM32_PIN(112, G, 8),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(115, C, 6),\
    __STM32_PIN(116, C, 7),\
    __STM32_PIN(117, C, 8),\
    __STM32_PIN(118, C, 9),\
    __STM32_PIN(119, A, 8),\
    __STM32_PIN(120, A, 9),\
    __STM32_PIN(121, A, 10),\
    __STM32_PIN(122, A, 11),\
    __STM32_PIN(123, A, 12),\
    __STM32_PIN(124, A, 13),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(128, H, 13),\
    __STM32_PIN(129, H, 14),\
    __STM32_PIN(130, H, 15),\
    __STM32_PIN(131, I, 0),\
    __STM32_PIN(132, I, 1),\
    __STM32_PIN(133, I, 2),\
    __STM32_PIN(134, I, 3),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(137, A, 14),\
    __STM32_PIN(138, A, 15),\
    __STM32_PIN(139, C, 10),\
    __STM32_PIN(140, C, 11),\
    __STM32_PIN(141, C, 12),\
    __STM32_PIN(142, D, 0),\
    __STM32_PIN(143, D, 1),\
    __STM32_PIN(144, D, 2),\
    __STM32_PIN(145, D, 3),\
    __STM32_PIN(146, D, 4),\
    __STM32_PIN(147, D, 5),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(150, D, 6),\
    __STM32_PIN(151, D, 7),\
    __STM32_PIN(152, G, 9),\
    __STM32_PIN(153, G, 10),\
    __STM32_PIN(154, G, 11),\
    __STM32_PIN(155, G, 12),\
    __STM32_PIN(156, G, 13),\
    __STM32_PIN(157, G, 14),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(160, G, 15),\
    __STM32_PIN(161, B, 3),\
    __STM32_PIN(162, B, 4),\
    __STM32_PIN(163, B, 5),\
    __STM32_PIN(164, B, 6),\
    __STM32_PIN(165, B, 7),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(167, B, 8),\
    __STM32_PIN(168, B, 9),\
    __STM32_PIN(169, E, 0),\
    __STM32_PIN(170, E, 1),\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN_DEFAULT,\
    __STM32_PIN(173, I, 4),\
    __STM32_PIN(174, I, 5),\
    __STM32_PIN(175, I, 6),\
    __STM32_PIN(176, I, 7),\
}



