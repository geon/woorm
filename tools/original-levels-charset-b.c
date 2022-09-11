#include "charset.h"

Charset originalLevelsCharsetB = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x3F, 0x3F, 0xFA, 0xEA, 0xEF, 0xFF, 0x3F, 0x3F},
	{0xFF, 0xFF, 0xBA, 0xBA, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFC, 0xDC, 0x9F, 0xAB, 0xFB, 0xCF, 0xF0, 0xFC},
	{0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00},
	{0xFF, 0xDF, 0xDA, 0xAA, 0xBF, 0xCF, 0x3F, 0xFF},
	{0xF0, 0xF0, 0xBC, 0xAC, 0xEC, 0xFC, 0xF0, 0xF0},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x3C, 0xFF, 0xFB, 0x69, 0x6D, 0xEF, 0xEF, 0xEF},
	{0x00, 0x00, 0x3C, 0xFF, 0xFB, 0x69, 0x6D, 0xEF},
	{0x00, 0x00, 0x00, 0x00, 0x3C, 0xFF, 0xFB, 0x69},
	{0x1E, 0x3F, 0xF8, 0xFF, 0xFF, 0xFF, 0x33, 0x33},
	{0x7F, 0x7F, 0x71, 0x21, 0x32, 0x3E, 0x3C, 0x1C},
	{0xFE, 0xFE, 0x8E, 0x84, 0x4C, 0x7C, 0x3C, 0x38},
	{0x2C, 0x3E, 0x9F, 0xF7, 0xF7, 0xBD, 0x3D, 0x2F},
	{0x3C, 0x3E, 0xFF, 0xF7, 0xDF, 0xFE, 0xF8, 0xFE},
	{0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00},
	{0xFF, 0xFF, 0xEA, 0xAA, 0xBF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xEA, 0xEA, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xF0, 0x70, 0x7C, 0xAC, 0xEC, 0x3C, 0xC0, 0xF0},
	{0x03, 0x03, 0x0F, 0x0E, 0x0E, 0x0F, 0x00, 0x03},
	{0xFF, 0x7F, 0x6A, 0xAA, 0xFF, 0x3F, 0xFF, 0xFF},
	{0xC0, 0xC0, 0xF0, 0xB0, 0xB0, 0xF0, 0xC0, 0xC0},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xEF, 0xEF, 0xFF, 0xFF, 0xEF, 0xEF, 0xEF, 0xEF},
	{0xEF, 0xEF, 0xEF, 0xEF, 0xFF, 0xFF, 0xEF, 0xEF},
	{0x6D, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xFF, 0xFF},
	{0x00, 0x00, 0x1C, 0x30, 0x3C, 0x3C, 0x14, 0x00},
	{0x1F, 0x15, 0x25, 0x28, 0x1A, 0x0F, 0x07, 0x00},
	{0xF8, 0x50, 0x44, 0x0C, 0xB8, 0xF0, 0xE0, 0x00},
	{0xBF, 0xF7, 0xDF, 0xFF, 0xBB, 0x23, 0x03, 0x00},
	{0x7F, 0xDF, 0xFE, 0xFC, 0x38, 0x00, 0xF0, 0xF0},
	{0x03, 0x03, 0x0F, 0x0E, 0x0E, 0x0F, 0x03, 0x03},
	{0xFF, 0xFF, 0xAB, 0xAB, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFD, 0xA9, 0xAA, 0xFF, 0xFC, 0xFF, 0xFF},
	{0xC0, 0xC0, 0xF0, 0xB0, 0xB0, 0xF0, 0x00, 0xC0},
	{0x0F, 0x0D, 0x3D, 0x3A, 0x3B, 0x3C, 0x03, 0x0F},
	{0xFF, 0xFF, 0xAB, 0xAA, 0xFE, 0xFF, 0xFF, 0xFF},
	{0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xFF, 0xFF, 0x3C},
	{0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0x55},
	{0x6F, 0x6F, 0x6F, 0x6F, 0x6F, 0x6F, 0x6A, 0x55},
	{0x0F, 0x1F, 0x3F, 0x3F, 0x31, 0x21, 0x32, 0x3E},
	{0xF0, 0xF8, 0xFC, 0xFC, 0x8C, 0x84, 0xCC, 0x7C},
	{0x1E, 0x1F, 0x77, 0x7B, 0x7B, 0x7D, 0x3D, 0x1F},
	{0x38, 0x78, 0xFE, 0xE7, 0xDF, 0xBE, 0xF8, 0xFE},
	{0x0F, 0x0F, 0x3E, 0x3A, 0x3B, 0x3F, 0x0F, 0x0F},
	{0xFF, 0xFF, 0xAE, 0xAE, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xF7, 0xA7, 0xAA, 0xFE, 0xF3, 0xFC, 0xFF},
	{0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00},
	{0x3F, 0x37, 0xF6, 0xEA, 0xEF, 0xF3, 0x0F, 0x3F},
	{0xFC, 0xFC, 0xAF, 0xAB, 0xFB, 0xFF, 0xFC, 0xFC},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xFF, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x6A, 0x6F, 0x6F, 0x6F, 0x6F, 0x6F, 0x6F, 0x6A},
	{0xAA, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xAA},
	{0x1E, 0x0F, 0x0A, 0x12, 0x14, 0x0D, 0x07, 0x03},
	{0x78, 0xF0, 0xA0, 0x88, 0x18, 0x70, 0xE0, 0xC0},
	{0x79, 0xF7, 0xEF, 0xFF, 0x3D, 0x39, 0x01, 0x00},
	{0xBF, 0xCF, 0xFE, 0xF8, 0xB8, 0x80, 0xE0, 0xE0},
	{0x00, 0x00, 0x00, 0x0F, 0x0F, 0x3F, 0x3E, 0xFA},
	{0x00, 0x00, 0x00, 0xF0, 0xF0, 0xAC, 0xAC, 0xAB},
	{0x00, 0x05, 0x01, 0x01, 0x01, 0x05, 0x05, 0x2A},
	{0x00, 0x50, 0x40, 0x40, 0x40, 0x50, 0x50, 0xA8},
	{0x00, 0x0F, 0x3D, 0xF5, 0xFF, 0x7F, 0x1F, 0x05},
	{0x00, 0xF0, 0xFC, 0xFF, 0xFF, 0xFD, 0xF4, 0x50},
	{0x00, 0x03, 0x01, 0x3F, 0xF7, 0xD5, 0x7D, 0x7F},
	{0x00, 0xC0, 0xC0, 0xFC, 0xDF, 0x57, 0x7D, 0x7D},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xD5, 0xEA, 0xE2},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x8B, 0xAB},
	{0x0F, 0x3D, 0x37, 0x37, 0x3F, 0x3F, 0x3F, 0x3F},
	{0xF0, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC},
	{0x3C, 0xFF, 0xFF, 0x3E, 0x02, 0x08, 0x08, 0x08},
	{0x00, 0x00, 0x30, 0xF0, 0x80, 0x80, 0x20, 0x20},
	{0x0F, 0x3D, 0x3F, 0xDF, 0xFE, 0xFE, 0xDC, 0xFC},
	{0xF0, 0xFC, 0x7C, 0xF7, 0xBD, 0xBF, 0x37, 0x3F},
	{0xFF, 0xCF, 0x33, 0x33, 0x0C, 0x0C, 0x03, 0x03},
	{0xFF, 0xAB, 0xAC, 0xAC, 0xB0, 0xB0, 0xC0, 0xC0},
	{0x3F, 0x37, 0x37, 0x3F, 0x37, 0x3F, 0x3F, 0x0F},
	{0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF0},
	{0x05, 0x10, 0x40, 0x40, 0x40, 0x10, 0x05, 0x00},
	{0x50, 0x04, 0x01, 0x01, 0x01, 0x04, 0x50, 0x00},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x2E, 0x2A, 0x2A},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xE8, 0xE8, 0xA8},
	{0xE8, 0xEA, 0xFA, 0xF8, 0x3E, 0x3F, 0x0F, 0x03},
	{0xAB, 0x8B, 0xAF, 0xAF, 0xBC, 0xFC, 0xF0, 0xC0},
	{0x3F, 0x1D, 0x15, 0x05, 0x01, 0x01, 0x01, 0x01},
	{0xFC, 0xDC, 0x54, 0x50, 0x40, 0x40, 0x40, 0x40},
	{0x20, 0x20, 0x20, 0x30, 0x7C, 0x7C, 0xFC, 0x30},
	{0x08, 0x08, 0x0C, 0x1F, 0x1F, 0x3F, 0x0C, 0x00},
	{0x7C, 0xFC, 0xDF, 0xBF, 0xBD, 0x2F, 0x2A, 0x0A},
	{0x3F, 0x37, 0xFF, 0xDE, 0xFE, 0xF8, 0xA8, 0xA0},
	{0x00, 0x00, 0x00, 0x83, 0x23, 0x0B, 0x0D, 0x07},
	{0x00, 0x00, 0xC0, 0xF0, 0xF0, 0x7C, 0xDC, 0x74},
	{0x00, 0x20, 0x88, 0x82, 0x00, 0x03, 0x03, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x50, 0x14, 0x05, 0x39, 0x3B, 0x3B, 0xEF, 0xEF},
	{0x3D, 0xC1, 0xFF, 0xFF, 0xFF, 0x7F, 0x15, 0x00},
	{0x00, 0x40, 0x50, 0xFC, 0xFF, 0xFF, 0xFD, 0x54},
	{0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
	{0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0x33, 0x33},
	{0xCC, 0x99, 0x33, 0x66, 0xCC, 0x99, 0x33, 0x66},
	{0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
	{0x18, 0x18, 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x18},
	{0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18},
	{0x3F, 0x37, 0x37, 0x0D, 0x03, 0x00, 0x00, 0x01},
	{0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xC0, 0xC0, 0xF0},
	{0x0C, 0x0C, 0x00, 0x33, 0x33, 0x00, 0xCC, 0xCC},
	{0xC0, 0xC0, 0x00, 0x30, 0x30, 0x00, 0xCC, 0xCC},
	{0x03, 0x0F, 0x3E, 0xFB, 0x2F, 0xFF, 0xFF, 0x3C},
	{0xBC, 0xBC, 0xFC, 0xF0, 0xF0, 0xC0, 0x00, 0x00},
	{0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0},
	{0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
	{0x57, 0x55, 0xDD, 0xDD, 0xDF, 0x7F, 0x7F, 0xFF},
	{0xFF, 0xFF, 0x7F, 0x7F, 0xDF, 0xDF, 0x77, 0x77},
	{0xF7, 0xD7, 0xDD, 0x7D, 0xF5, 0xD5, 0xFD, 0x00},
	{0x00, 0xF5, 0xD5, 0xF5, 0x7D, 0xDD, 0xD7, 0xF7},
	{0x77, 0x77, 0xDF, 0xDF, 0x7F, 0x7F, 0xFF, 0xFC},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00, 0x00},
	{0x3E, 0x7F, 0x49, 0x77, 0x3E, 0x14, 0x2A, 0x1C},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xF4, 0xFD, 0xFF, 0xFF, 0xFF, 0x7F, 0x5F, 0x1F},
	{0xFF, 0xAA, 0xAA, 0xAA, 0xFF, 0xFF, 0x55, 0xFF},
	{0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF},
	{0x00, 0x7F, 0x57, 0x5F, 0x7D, 0x77, 0xD7, 0xDF},
	{0xFC, 0xFC, 0xDC, 0xDC, 0x5C, 0x74, 0x54, 0xD4},
	{0x00, 0x07, 0x1F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF},
	{0x00, 0x80, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF},
	{0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18},
	{0x00, 0x00, 0x05, 0x17, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x00, 0x00, 0x70, 0xDC, 0xF4, 0xFC, 0xF4, 0xFC},
	{0x00, 0x00, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xF4, 0xFC, 0xF4, 0xFC, 0xF4, 0xFC, 0xF4, 0xFC},
	{0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xF4, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0x55, 0x55, 0x00, 0x55, 0xFF, 0xAA},
	{0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1},
	{0xDD, 0xDD, 0xF7, 0xF7, 0xFD, 0xFD, 0xFF, 0xFF},
	{0x00, 0x07, 0x1F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFD, 0xFD, 0xF7, 0xF7, 0xDD, 0xDD},
	{0xD4, 0x54, 0x74, 0x5C, 0xDC, 0xDC, 0xFC, 0xFC},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x55, 0x57, 0x57, 0x75, 0xFD, 0xFD, 0xFD, 0x75},
	{0x0F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F},
	{0xF0, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0},
	{0x00, 0x00, 0x00, 0x1F, 0x1F, 0x18, 0x18, 0x18},
	{0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18},
	{0xFF, 0xFF, 0xFF, 0xFF, 0x77, 0xDD, 0x00, 0x00},
	{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x7F, 0x1F},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF7, 0xFC},
	{0x0B, 0x2D, 0x35, 0xB5, 0xD5, 0xD7, 0xDF, 0xDF},
	{0xE0, 0x78, 0x5C, 0x7E, 0xFF, 0xEB, 0xAA, 0xEA},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F, 0x07, 0x00},
	{0xDF, 0xD7, 0x77, 0x7D, 0x5F, 0x57, 0x7F, 0x00},
	{0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0x80, 0x00},
	{0x3C, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF, 0x3F, 0x0C},
	{0x82, 0xFE, 0x82, 0x82, 0x82, 0xFE, 0x82, 0x82},
	{0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x00},
	{0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0x00},
	{0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00},
	{0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00, 0x00},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD},
	{0xC3, 0x99, 0xF9, 0xE3, 0xF9, 0x99, 0xC3, 0xFF},
	{0xF9, 0xF1, 0xE1, 0x99, 0x80, 0xF9, 0xF9, 0xFF},
	{0xFF, 0xFF, 0xEB, 0xFA, 0xBA, 0x1E, 0x27, 0x0D},
	{0xE2, 0xA2, 0x82, 0x82, 0x0A, 0xAC, 0xD8, 0x70},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x3F, 0x3F, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x30, 0x30, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C},
	{0x55, 0x77, 0x5F, 0x77, 0x5F, 0x77, 0x5F, 0xFF},
	{0xFF, 0xFB, 0xEA, 0xEA, 0xFB, 0xCC, 0xC0, 0xF3},
	{0xFB, 0xFB, 0xFB, 0x00, 0xDF, 0xDF, 0xDF, 0x00},
	{0x57, 0x5F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFE, 0xFA},
	{0x00, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x07, 0x0F, 0x1C, 0x18, 0x18},
	{0x00, 0x00, 0x00, 0xE0, 0xF0, 0x38, 0x18, 0x18},
	{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18},
	{0x00, 0x00, 0x00, 0x07, 0x0F, 0x1F, 0x1F, 0x1F},
	{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8},
	{0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x80, 0x32, 0xF2, 0x0A, 0xA8, 0xA3, 0x0F, 0x0F},
	{0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C},
	{0x00, 0x00, 0x00, 0xFF, 0xFF, 0x18, 0x18, 0x18},
	{0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18},
	{0x00, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x00},
	{0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
	{0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
	{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
	{0x18, 0x18, 0x1C, 0x0F, 0x07, 0x00, 0x00, 0x00},
	{0x18, 0x18, 0x38, 0xF0, 0xE0, 0x00, 0x00, 0x00},
	{0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00},
	{0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00},
	{0xF8, 0xF8, 0xF8, 0xF0, 0xE0, 0x00, 0x00, 0x00},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00},
	{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x00, 0xFF, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},
	{0x3C, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00},
	{0x18, 0x18, 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x18},
	{0x18, 0x18, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00},
	{0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E},
	{0x55, 0x57, 0x7F, 0x77, 0x77, 0x57, 0x7F, 0xFF},
	{0x00, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x00},
	{0x00, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0x00},
	{0x00, 0x07, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7E},
	{0x00, 0xE0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0x7E},
	{0x00, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E},
	{0x00, 0x07, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F},
	{0x00, 0xE0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE},
	{0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE},
	{0x00, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x00},
	{0x38, 0x7C, 0xFE, 0xFE, 0xFE, 0x7C, 0x38, 0x00},
	{0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E},
	{0x7E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x7E},
	{0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0x78, 0x30},
	{0x3E, 0x3E, 0x3E, 0x7E, 0x7E, 0x7C, 0x7C, 0x7C},
	{0xF5, 0xD7, 0x5F, 0x7D, 0xF5, 0xD7, 0x5F, 0x7D},
	{0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
	{0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E},
	{0x7E, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x07, 0x00},
	{0x7E, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xE0, 0x00},
	{0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x00},
	{0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x07, 0x00},
	{0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xE0, 0x00},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
	{0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0x3C, 0x96, 0xFF, 0x7B, 0xE2, 0xCA, 0xBE, 0x28},
	{0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E},
	{0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
	{0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8},
	{0x0E, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3E, 0x3E},
	{0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF},
};