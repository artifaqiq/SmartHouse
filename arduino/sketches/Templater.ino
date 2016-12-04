String JSON_SENSORS_TEMPLATE("{\"temperature\":<%t%>,\"humidity\":<%h%>,\"illumination\":<%i%>, \"token\": \"12345678\"}");

String getSensorsInfoJson(int temp, int hum, int ill) {
 String result(JSON_SENSORS_TEMPLATE);

 result.replace("<%t%>", String(temp));
 result.replace("<%h%>", String(hum));
 result.replace("<%i%>", String(ill));

 return result;
}

