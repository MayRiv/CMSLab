-- phpMyAdmin SQL Dump
-- version 4.0.9
-- http://www.phpmyadmin.net
--
-- Хост: 127.0.0.1
-- Время создания: Сен 03 2014 г., 10:16
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
  PRIMARY KEY (`Id`),
  KEY `InstanceOf` (`InstanceOf`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Дамп данных таблицы `news`
--

INSERT INTO `news` (`Id`, `InstanceOf`, `Title`, `Body`, `ParentId`, `sortField`) VALUES
(1, NULL, 'Geopolitical situation', '', NULL, 'title'),
(2, NULL, 'Vladimir Putin and Petro Poroshenko discuss ''way out'' of Ukraine crisis', 'Vladimir Putin "to large extent" agrees with his Ukrainian counterpart, his spokesman says, as reports of 70 Russian paratroopers and an embedded Russian journalist killed in Ukraine emerge\r\n', 3, 'title'),
(3, NULL, 'Ukraine Crisis', '', 1, 'title');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
