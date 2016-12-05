String JSON_SENSORS_TEMPLATE("{\"temperature\":<%t%>,\"humidity\":<%h%>,\"illumination\":<%i%>, \"token\": \"12345678\"}");

String getSensorsInfoJson(int temp, int hum, int ill) {
 String result(JSON_SENSORS_TEMPLATE);

 result.replace("<%t%>", String(temp));
 result.replace("<%h%>", String(hum));
 result.replace("<%i%>", String(ill));

 return result;
}

String JSON_RELAY_TEMPLATE("{\"relay1_actual\":<%1%>,\"token\":\"12345678\"}");

String getRelayStatusJson(boolean relay1_actual) {
  String result(JSON_RELAY_TEMPLATE);

  result.replace("<%1%>", relay1_actual ? "true" : "false");

  return result;
}

