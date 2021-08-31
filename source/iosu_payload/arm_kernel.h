static const unsigned char arm_kernel_bin[] = {
  0xea, 0x00, 0x00, 0x0e, 0xe1, 0xa0, 0x30, 0x00, 0xe1, 0xa0, 0x20, 0x03,
  0xe5, 0xd2, 0x10, 0x00, 0xe2, 0x83, 0x30, 0x01, 0xe3, 0x51, 0x00, 0x00,
  0x1a, 0xff, 0xff, 0xfa, 0xe0, 0x42, 0x00, 0x00, 0xe1, 0x2f, 0xff, 0x1e,
  0xe3, 0xa0, 0x30, 0x00, 0xe1, 0x53, 0x00, 0x02, 0x01, 0x2f, 0xff, 0x1e,
  0xe7, 0xd1, 0xc0, 0x03, 0xe7, 0xc0, 0xc0, 0x03, 0xe2, 0x83, 0x30, 0x01,
  0xea, 0xff, 0xff, 0xf9, 0xe9, 0x2d, 0x41, 0xf0, 0xe5, 0x9f, 0x11, 0x5c,
  0xe5, 0x9f, 0x31, 0x5c, 0xe3, 0xa0, 0x2b, 0x01, 0xe3, 0xa0, 0x00, 0x00,
  0xe1, 0x2f, 0xff, 0x33, 0xeb, 0x00, 0x00, 0x64, 0xe5, 0x9f, 0x41, 0x4c,
  0xe3, 0xa0, 0x70, 0x00, 0xe1, 0xa0, 0x60, 0x00, 0xeb, 0x00, 0x00, 0x69,
  0xe1, 0xa0, 0x50, 0x00, 0xeb, 0x00, 0x00, 0x62, 0xe3, 0x85, 0x00, 0xc0,
  0xeb, 0x00, 0x00, 0x67, 0xe3, 0xc6, 0x0a, 0x01, 0xe3, 0xc0, 0x00, 0x05,
  0xeb, 0x00, 0x00, 0x5b, 0xe5, 0x9f, 0x31, 0x24, 0xe5, 0x9f, 0x21, 0x24,
  0xe5, 0x9f, 0x11, 0x24, 0xe5, 0x83, 0x2a, 0x24, 0xe5, 0x9f, 0x01, 0x20,
  0xe3, 0xa0, 0x20, 0x38, 0xeb, 0xff, 0xff, 0xdf, 0xe5, 0x9f, 0x31, 0x18,
  0xe5, 0x9f, 0x01, 0x18, 0xe5, 0x93, 0x2d, 0x18, 0xe5, 0x9f, 0x31, 0x14,
  0xe2, 0x81, 0x10, 0x38, 0xe5, 0x83, 0x20, 0x00, 0xe3, 0xa0, 0x20, 0x68,
  0xeb, 0xff, 0xff, 0xd7, 0xe3, 0xa0, 0x39, 0x52, 0xe2, 0x80, 0x0a, 0x31,
  0xe5, 0x93, 0x20, 0x00, 0xe5, 0x9f, 0x10, 0xf8, 0xe2, 0x80, 0x0f, 0x57,
  0xeb, 0xff, 0xff, 0xd1, 0xe5, 0x9f, 0x30, 0xf0, 0xe5, 0x9f, 0x20, 0xf0,
  0xe5, 0x83, 0x2f, 0x78, 0xe1, 0xa0, 0x00, 0x04, 0xeb, 0xff, 0xff, 0xc4,
  0xe2, 0x87, 0x70, 0x01, 0xe1, 0xa0, 0x10, 0x04, 0xe2, 0x84, 0x40, 0x54,
  0xe2, 0x80, 0x20, 0x01, 0xe5, 0x14, 0x00, 0x58, 0xeb, 0xff, 0xff, 0xc6,
  0xe3, 0x57, 0x00, 0x19, 0x1a, 0xff, 0xff, 0xf5, 0xe1, 0xa0, 0x00, 0x06,
  0xeb, 0x00, 0x00, 0x37, 0xe5, 0x9f, 0x10, 0xbc, 0xe5, 0x9f, 0x00, 0xbc,
  0xe5, 0x9f, 0x30, 0xbc, 0xe1, 0x2f, 0xff, 0x33, 0xe5, 0x9f, 0x30, 0xb8,
  0xe1, 0x2f, 0xff, 0x33, 0xe1, 0xa0, 0x00, 0x05, 0xeb, 0x00, 0x00, 0x38,
  0xe5, 0x9f, 0x40, 0xac, 0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00,
  0xe3, 0xa0, 0x10, 0x0b, 0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34,
  0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00, 0xe3, 0xa0, 0x10, 0x0d,
  0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34, 0xe3, 0xe0, 0x30, 0x00,
  0xe3, 0xe0, 0x20, 0x00, 0xe3, 0xa0, 0x10, 0x0f, 0xe3, 0xa0, 0x00, 0x15,
  0xe1, 0x2f, 0xff, 0x34, 0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00,
  0xe3, 0xa0, 0x10, 0x10, 0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34,
  0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00, 0xe3, 0xa0, 0x10, 0x16,
  0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34, 0xe3, 0xa0, 0x00, 0x00,
  0xe8, 0xbd, 0x81, 0xf0, 0x01, 0xff, 0xf0, 0x00, 0x08, 0x12, 0x02, 0x48,
  0x08, 0x13, 0x52, 0xc8, 0x08, 0x12, 0x90, 0x00, 0xe1, 0x2f, 0xff, 0x1e,
  0x08, 0x13, 0x52, 0x24, 0x08, 0x12, 0x00, 0x00, 0x10, 0x16, 0xa0, 0x00,
  0x10, 0x10, 0x01, 0x74, 0x00, 0x12, 0xf0, 0x00, 0x00, 0x14, 0x80, 0x04,
  0x12, 0xbd, 0x90, 0x00, 0xe3, 0xa0, 0x00, 0x01, 0x00, 0x00, 0x40, 0x01,
  0x08, 0x12, 0x98, 0xbc, 0x08, 0x12, 0x01, 0x64, 0x08, 0x12, 0xdc, 0xf0,
  0x08, 0x12, 0x60, 0xa8, 0xee, 0x11, 0x0f, 0x10, 0xe1, 0x2f, 0xff, 0x1e,
  0xee, 0x01, 0x0f, 0x10, 0xe1, 0x2f, 0xff, 0x1e, 0xee, 0x17, 0xff, 0x7a,
  0x1a, 0xff, 0xff, 0xfd, 0xe3, 0xa0, 0x00, 0x00, 0xee, 0x07, 0x0f, 0x9a,
  0xe1, 0x2f, 0xff, 0x1e, 0xe1, 0x0f, 0x00, 0x00, 0xe1, 0x2f, 0xff, 0x1e,
  0xe1, 0x29, 0xf0, 0x00, 0xe1, 0x2f, 0xff, 0x1e, 0xe9, 0x2d, 0x40, 0x30,
  0xe1, 0xa0, 0x40, 0x00, 0xeb, 0x00, 0x39, 0xda, 0xe5, 0x9f, 0x30, 0x1c,
  0xe1, 0xa0, 0x50, 0x00, 0xe1, 0xa0, 0x00, 0x04, 0xe1, 0x2f, 0xff, 0x33,
  0xe1, 0xa0, 0x40, 0x00, 0xe1, 0xa0, 0x00, 0x05, 0xeb, 0x00, 0x39, 0xd8,
  0xe1, 0xa0, 0x00, 0x04, 0xe8, 0xbd, 0x80, 0x30, 0xff, 0xff, 0xe3, 0xec,
  0xe9, 0x2d, 0x40, 0x30, 0xe5, 0x8d, 0xe0, 0x04, 0xe5, 0x8d, 0xc0, 0x08,
  0xe5, 0x8d, 0x40, 0x0c, 0xe5, 0x8d, 0x60, 0x10, 0xeb, 0x00, 0xb2, 0xfd,
  0xea, 0xff, 0xff, 0xc9, 0x10, 0x14, 0x03, 0xf8, 0x10, 0x62, 0x4d, 0xd3,
  0x10, 0x14, 0x50, 0x00, 0x10, 0x14, 0x50, 0x20, 0x10, 0x14, 0x00, 0x00,
  0x10, 0x14, 0x00, 0x90, 0x10, 0x14, 0x00, 0x70, 0x10, 0x14, 0x00, 0x98,
  0x10, 0x14, 0x00, 0x84, 0x10, 0x14, 0x03, 0xe8, 0x10, 0x14, 0x00, 0x3c,
  0x00, 0x00, 0x01, 0x73, 0x00, 0x00, 0x01, 0x76, 0xe9, 0x2d, 0x4f, 0xf0,
  0xe2, 0x4d, 0xde, 0x17, 0xeb, 0x00, 0xb9, 0x92, 0xe3, 0xa0, 0x10, 0x00,
  0xe3, 0xa0, 0x20, 0x03, 0xe5, 0x9f, 0x0e, 0x68, 0xeb, 0x00, 0xb3, 0x20,
  0x13, 0x14, 0x25, 0x50, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x70,
  0x75, 0x73, 0x68, 0x6d, 0x6f, 0x72, 0x65, 0x2e, 0x77, 0x75, 0x70, 0x2e,
  0x73, 0x68, 0x6f, 0x70, 0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64,
  0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x70, 0x75, 0x73, 0x68, 0x6d, 0x6f, 0x72,
  0x65, 0x2f, 0x72, 0x2f, 0x25, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xa0, 0xa0, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e,
  0x70, 0x6e, 0x73, 0x2d, 0x64, 0x65, 0x76, 0x2e, 0x63, 0x2e, 0x61, 0x70,
  0x70, 0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63,
  0x63, 0x2f, 0x62, 0x73, 0x74, 0x2e, 0x64, 0x61, 0x74, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xa0, 0xd0, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e,
  0x70, 0x6e, 0x73, 0x2d, 0x64, 0x65, 0x76, 0x2e, 0x63, 0x2e, 0x61, 0x70,
  0x70, 0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63,
  0x63, 0x2f, 0x62, 0x73, 0x74, 0x32, 0x2e, 0x64, 0x61, 0x74, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x19, 0x64, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x74, 0x61, 0x67, 0x61, 0x79, 0x61, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73,
  0x68, 0x6f, 0x70, 0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f,
  0x2e, 0x63, 0x63, 0x2f, 0x74, 0x61, 0x67, 0x61, 0x79, 0x61, 0x2f, 0x76,
  0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x6c, 0x69, 0x73, 0x74, 0x2f, 0x25,
  0x73, 0x2f, 0x25, 0x73, 0x2f, 0x25, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x19, 0xb4, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x74, 0x61, 0x67, 0x61, 0x79, 0x61, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73,
  0x68, 0x6f, 0x70, 0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f,
  0x2e, 0x63, 0x63, 0x2f, 0x74, 0x61, 0x67, 0x61, 0x79, 0x61, 0x2f, 0x76,
  0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x6c, 0x69, 0x73, 0x74, 0x2f, 0x25,
  0x73, 0x2f, 0x25, 0x73, 0x2f, 0x6c, 0x61, 0x74, 0x65, 0x73, 0x74, 0x5f,
  0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x25, 0x84, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x70,
  0x75, 0x73, 0x68, 0x6d, 0x6f, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73, 0x68,
  0x6f, 0x70, 0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e,
  0x63, 0x63, 0x2f, 0x70, 0x75, 0x73, 0x68, 0x6d, 0x6f, 0x2f, 0x64, 0x2f,
  0x25, 0x73, 0x2f, 0x25, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x25, 0xb8, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x70,
  0x75, 0x73, 0x68, 0x6d, 0x6f, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73, 0x68,
  0x6f, 0x70, 0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e,
  0x63, 0x63, 0x2f, 0x70, 0x75, 0x73, 0x68, 0x6d, 0x6f, 0x2f, 0x63, 0x2f,
  0x25, 0x75, 0x2f, 0x25, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x2d, 0xb4, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x65, 0x63, 0x73, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73, 0x68, 0x6f, 0x70,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x2f, 0x65, 0x63, 0x73, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
  0x73, 0x2f, 0x45, 0x43, 0x6f, 0x6d, 0x6d, 0x65, 0x72, 0x63, 0x65, 0x53,
  0x4f, 0x41, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x30, 0xa0, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x65, 0x63, 0x73, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73, 0x68, 0x6f, 0x70,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x2f, 0x65, 0x63, 0x73, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
  0x73, 0x2f, 0x45, 0x43, 0x6f, 0x6d, 0x6d, 0x65, 0x72, 0x63, 0x65, 0x53,
  0x4f, 0x41, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x30, 0xe0, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x6e, 0x75, 0x73, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73, 0x68, 0x6f, 0x70,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x2f, 0x6e, 0x75, 0x73, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
  0x73, 0x2f, 0x4e, 0x65, 0x74, 0x55, 0x70, 0x64, 0x61, 0x74, 0x65, 0x53,
  0x4f, 0x41, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0x99, 0x90, 0x6e, 0x70, 0x70, 0x6c, 0x2e, 0x61, 0x70, 0x70,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xa6, 0x00, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x70, 0x6c, 0x73, 0x2e, 0x77, 0x75, 0x70, 0x2e, 0x73, 0x68, 0x6f, 0x70,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x2f, 0x70, 0x6c, 0x73, 0x2f, 0x75, 0x70, 0x6c, 0x6f, 0x61, 0x64, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xa6, 0xac, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x6e, 0x70, 0x76, 0x6b, 0x2d, 0x64, 0x65, 0x76, 0x2e, 0x61, 0x70, 0x70,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x2f, 0x72, 0x65, 0x70, 0x6f, 0x72, 0x74, 0x73, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xa6, 0xd8, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x6e, 0x70, 0x76, 0x6b, 0x2e, 0x61, 0x70, 0x70, 0x2e, 0x70, 0x72, 0x65,
  0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x72, 0x65, 0x70,
  0x6f, 0x72, 0x74, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xb1, 0xf4, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x6e, 0x70, 0x74, 0x73, 0x2e, 0x61, 0x70, 0x70, 0x2e, 0x70, 0x72, 0x65,
  0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x70, 0x30, 0x31,
  0x2f, 0x74, 0x61, 0x73, 0x6b, 0x73, 0x68, 0x65, 0x65, 0x74, 0x2f, 0x25,
  0x73, 0x2f, 0x25, 0x73, 0x2f, 0x25, 0x73, 0x2f, 0x25, 0x73, 0x3f, 0x63,
  0x3d, 0x25, 0x73, 0x26, 0x6c, 0x3d, 0x25, 0x73, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xb2, 0x38, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x6e, 0x70, 0x74, 0x73, 0x2e, 0x61, 0x70, 0x70, 0x2e, 0x70, 0x72, 0x65,
  0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x70, 0x30, 0x31,
  0x2f, 0x74, 0x61, 0x73, 0x6b, 0x73, 0x68, 0x65, 0x65, 0x74, 0x2f, 0x25,
  0x73, 0x2f, 0x25, 0x73, 0x2f, 0x25, 0x73, 0x3f, 0x63, 0x3d, 0x25, 0x73,
  0x26, 0x6c, 0x3d, 0x25, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x16, 0xb2, 0xd8, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x69, 0x64, 0x62, 0x65, 0x2d, 0x77, 0x75, 0x70, 0x2e, 0x63, 0x64, 0x6e,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x2f, 0x69, 0x63, 0x6f, 0x6e, 0x64, 0x61, 0x74, 0x61, 0x2f, 0x25, 0x30,
  0x32, 0x58, 0x2f, 0x25, 0x30, 0x31, 0x36, 0x6c, 0x6c, 0x58, 0x2e, 0x69,
  0x64, 0x62, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x16, 0xb3, 0x58, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x69, 0x64, 0x62, 0x65, 0x2d, 0x77, 0x75, 0x70, 0x2e, 0x63, 0x64, 0x6e,
  0x2e, 0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63,
  0x2f, 0x69, 0x63, 0x6f, 0x6e, 0x64, 0x61, 0x74, 0x61, 0x2f, 0x25, 0x30,
  0x32, 0x58, 0x2f, 0x25, 0x30, 0x31, 0x36, 0x6c, 0x6c, 0x58, 0x2d, 0x25,
  0x64, 0x2e, 0x69, 0x64, 0x62, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x17, 0x3e, 0xf8, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x65, 0x63, 0x73, 0x2e, 0x63, 0x2e, 0x73, 0x68, 0x6f, 0x70, 0x2e, 0x70,
  0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x17, 0x3f, 0x30, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x65, 0x63, 0x73, 0x2e, 0x63, 0x2e, 0x73, 0x68, 0x6f, 0x70, 0x2e, 0x70,
  0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x65,
  0x63, 0x73, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x2f,
  0x45, 0x43, 0x6f, 0x6d, 0x6d, 0x65, 0x72, 0x63, 0x65, 0x53, 0x4f, 0x41,
  0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x17, 0x3f, 0x70, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x69, 0x61, 0x73, 0x2e, 0x63, 0x2e, 0x73, 0x68, 0x6f, 0x70, 0x2e, 0x70,
  0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x69,
  0x61, 0x73, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x2f,
  0x49, 0x64, 0x65, 0x6e, 0x74, 0x69, 0x74, 0x79, 0x41, 0x75, 0x74, 0x68,
  0x65, 0x6e, 0x74, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x53, 0x4f,
  0x41, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x17, 0x3f, 0xbc, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x63, 0x61, 0x73, 0x2e, 0x63, 0x2e, 0x73, 0x68, 0x6f, 0x70, 0x2e, 0x70,
  0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x63,
  0x61, 0x73, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x2f,
  0x43, 0x61, 0x74, 0x61, 0x6c, 0x6f, 0x67, 0x69, 0x6e, 0x67, 0x53, 0x4f,
  0x41, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x17, 0x3f, 0xfc, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x6e, 0x75, 0x73, 0x2e, 0x63, 0x2e, 0x73, 0x68, 0x6f, 0x70, 0x2e, 0x70,
  0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f, 0x6e,
  0x75, 0x73, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x2f,
  0x4e, 0x65, 0x74, 0x55, 0x70, 0x64, 0x61, 0x74, 0x65, 0x53, 0x4f, 0x41,
  0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x15, 0xde, 0x0c, 0x6e, 0x2e, 0x61, 0x70, 0x70, 0x2e, 0x70, 0x72,
  0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x7d, 0x30, 0xd4, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x25, 0x73, 0x25, 0x73, 0x61, 0x63, 0x63, 0x6f, 0x75, 0x6e, 0x74, 0x2e,
  0x70, 0x72, 0x65, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x2e, 0x63, 0x63, 0x2f,
  0x76, 0x25, 0x75, 0x2f, 0x61, 0x70, 0x69, 0x2f, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const unsigned int arm_kernel_bin_len = 2808;
