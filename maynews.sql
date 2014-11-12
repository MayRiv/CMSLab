-- phpMyAdmin SQL Dump
-- version 4.0.9
-- http://www.phpmyadmin.net
--
-- Хост: 127.0.0.1
-- Время создания: Ноя 12 2014 г., 04:26
-- Версия сервера: 5.6.14
-- Версия PHP: 5.5.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `maynews`
--
CREATE DATABASE IF NOT EXISTS `maynews` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `maynews`;

-- --------------------------------------------------------

--
-- Структура таблицы `filters`
--

CREATE TABLE IF NOT EXISTS `filters` (
  `FilterId` int(11) NOT NULL AUTO_INCREMENT,
  `Caption` text NOT NULL,
  `AndLogic` tinyint(1) NOT NULL,
  PRIMARY KEY (`FilterId`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `filters`
--

INSERT INTO `filters` (`FilterId`, `Caption`, `AndLogic`) VALUES
(1, 'Author', 0),
(2, 'Additional', 1);

-- --------------------------------------------------------

--
-- Структура таблицы `filtervalues`
--

CREATE TABLE IF NOT EXISTS `filtervalues` (
  `FilterValueId` int(11) NOT NULL AUTO_INCREMENT,
  `FilterId` int(11) NOT NULL,
  `Caption` text NOT NULL,
  PRIMARY KEY (`FilterValueId`),
  KEY `FilterId` (`FilterId`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- СВЯЗИ ТАБЛИЦЫ `filtervalues`:
--   `FilterId`
--       `filters` -> `FilterId`
--

--
-- Дамп данных таблицы `filtervalues`
--

INSERT INTO `filtervalues` (`FilterValueId`, `FilterId`, `Caption`) VALUES
(1, 1, 'May'),
(2, 1, 'Cuber'),
(3, 2, 'War'),
(4, 2, 'Short');

-- --------------------------------------------------------

--
-- Структура таблицы `filtervaluesnews`
--

CREATE TABLE IF NOT EXISTS `filtervaluesnews` (
  `FilterValueId` int(11) NOT NULL,
  `NewsId` int(11) NOT NULL,
  KEY `FilterValueId` (`FilterValueId`,`NewsId`),
  KEY `NewsId` (`NewsId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- СВЯЗИ ТАБЛИЦЫ `filtervaluesnews`:
--   `FilterValueId`
--       `filtervalues` -> `FilterValueId`
--   `NewsId`
--       `news` -> `Id`
--

--
-- Дамп данных таблицы `filtervaluesnews`
--

INSERT INTO `filtervaluesnews` (`FilterValueId`, `NewsId`) VALUES
(1, 2),
(1, 10),
(2, 8),
(2, 9),
(3, 9),
(3, 10),
(4, 9);

-- --------------------------------------------------------

--
-- Структура таблицы `news`
--

CREATE TABLE IF NOT EXISTS `news` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `InstanceOf` int(11) DEFAULT NULL,
  `Title` text CHARACTER SET cp1251 NOT NULL,
  `Body` text NOT NULL,
  `ParentId` int(11) DEFAULT NULL,
  `sortField` text NOT NULL,
  `IsContainer` tinyint(1) NOT NULL,
  PRIMARY KEY (`Id`),
  KEY `InstanceOf` (`InstanceOf`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

--
-- Дамп данных таблицы `news`
--

INSERT INTO `news` (`Id`, `InstanceOf`, `Title`, `Body`, `ParentId`, `sortField`, `IsContainer`) VALUES
(1, NULL, 'Geopolitical situation', '', NULL, 'title', 1),
(2, NULL, 'Vladimir Putin and Petro Poroshenko discuss ''way out'' of Ukraine crisis', 'Vladimir Putin "to large extent" agrees with his Ukrainian counterpart, his spokesman says, as reports of 70 Russian paratroopers and an embedded Russian journalist killed in Ukraine emerge\r\n', 3, 'title', 0),
(3, NULL, 'Ukraine Crisis', '', 1, 'title', 1),
(6, NULL, 'Sport', '', NULL, 'title', 1),
(7, NULL, 'Olympic', '', 6, 'title', 1),
(8, NULL, 'Sochi 2014’s ‘human’ legacy set to come to life ', 'Following the success of the country’s first Olympic Winter Games, Russia is now set to host several other major sporting events, including the inaugural Russian Formula One Grand Prix in October, the 2016 FIH Ice Hockey World Championships, the 2017 FIBT Bob & Skeleton World Championships and the 2018 FIFA World Cup.\r\nAt the heart of these events will be many of the people who worked tirelessly to ensure the success of Sochi 2014, with the experience and skills they gained during preparations for the Winter Games set to benefit these and other major events.', 7, 'title', 0),
(9, NULL, 'Intervantion', 'Russion army has intervented into Ukrain', 3, 'title', 0),
(10, NULL, '2014 pro-Russian unrest in Ukraine', 'Since the end of February 2014, demonstrations by pro-Russian and anti-government groups have taken place in major cities across the eastern and southern regions of Ukraine, in the aftermath of the Euromaidan movement and the 2014 Ukrainian revolution. During the first stage of the unrest, Crimea was annexed by the Russian Federation after a crisis in the region, Russian military intervention and an internationally criticized referendum. Protests in Donetsk and Luhansk oblasts escalated into an armed separatist insurgency.[57][58] This led the Ukrainian government to launch a military counter-offensive against the insurgents, which resulted in the ongoing War in Donbass.[59]', 3, 'title', 0);

-- --------------------------------------------------------

--
-- Структура таблицы `newstablevalues`
--

CREATE TABLE IF NOT EXISTS `newstablevalues` (
  `NewsId` int(11) NOT NULL,
  `TableValueId` int(11) NOT NULL,
  `Value` varchar(30) NOT NULL,
  KEY `NewsId` (`NewsId`,`TableValueId`),
  KEY `TableValueId` (`TableValueId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- СВЯЗИ ТАБЛИЦЫ `newstablevalues`:
--   `NewsId`
--       `news` -> `Id`
--   `TableValueId`
--       `tablevalues` -> `TableValueId`
--

--
-- Дамп данных таблицы `newstablevalues`
--

INSERT INTO `newstablevalues` (`NewsId`, `TableValueId`, `Value`) VALUES
(9, 1, '100'),
(10, 1, '50'),
(9, 2, 'OLD'),
(10, 2, 'HOT');

-- --------------------------------------------------------

--
-- Структура таблицы `tablevalues`
--

CREATE TABLE IF NOT EXISTS `tablevalues` (
  `TableValueId` int(11) NOT NULL AUTO_INCREMENT,
  `Caption` varchar(20) NOT NULL,
  PRIMARY KEY (`TableValueId`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `tablevalues`
--

INSERT INTO `tablevalues` (`TableValueId`, `Caption`) VALUES
(1, 'Number of dead'),
(2, 'Actuality');

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `filtervalues`
--
ALTER TABLE `filtervalues`
  ADD CONSTRAINT `filtervalues_ibfk_1` FOREIGN KEY (`FilterId`) REFERENCES `filters` (`FilterId`);

--
-- Ограничения внешнего ключа таблицы `filtervaluesnews`
--
ALTER TABLE `filtervaluesnews`
  ADD CONSTRAINT `filtervaluesnews_ibfk_1` FOREIGN KEY (`FilterValueId`) REFERENCES `filtervalues` (`FilterValueId`),
  ADD CONSTRAINT `filtervaluesnews_ibfk_2` FOREIGN KEY (`NewsId`) REFERENCES `news` (`Id`);

--
-- Ограничения внешнего ключа таблицы `newstablevalues`
--
ALTER TABLE `newstablevalues`
  ADD CONSTRAINT `newstablevalues_ibfk_1` FOREIGN KEY (`NewsId`) REFERENCES `news` (`Id`),
  ADD CONSTRAINT `newstablevalues_ibfk_2` FOREIGN KEY (`TableValueId`) REFERENCES `tablevalues` (`TableValueId`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
