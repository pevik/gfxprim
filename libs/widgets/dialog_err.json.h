static const char *dialog_err = "\
{ \
 \"version\": 1, \
 \"widgets\": [ \
  { \
   \"type\": \"frame\", \
   \"label\": \"Error\", \
   \"widget\": { \
    \"rows\": 2, \
    \"widgets\": [ \
     { \
      \"cols\": 2, \
      \"frame\": \"none\", \
      \"widgets\": [ \
       { \
        \"type\": \"stock\", \
        \"stock\": \"err\" \
       }, \
       { \
        \"type\": \"label\", \
        \"uid\": \"text\" \
       } \
      ] \
     }, \
     { \
      \"type\": \"button\", \
      \"label\": \"OK\", \
      \"uid\": \"btn_ok\" \
     } \
    ] \
   } \
  } \
 ] \
} \
";