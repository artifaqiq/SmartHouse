$(document).ready ->
  checkState()
  setInterval(checkState, 500)

checkState = ->
   $.get '/api/states/show',
     (data) -> setStatus(data.relay1_actual)
   $.get '/api/sensors/online',
     (obj) -> setSensors(obj)


setStatus = (status) ->
  if status
    document.getElementById("button_relay1").textContent = "OFF"
    document.getElementById("h3_relay1").textContent = "Status: ON"
  else
    document.getElementById("button_relay1").textContent = "ON"
    document.getElementById("h3_relay1").textContent = "Status: OFF"

setSensors = (obj) ->
  document.getElementById("temperature").textContent = obj.temperature + " °C"
  document.getElementById("humidity").textContent = obj.humidity + " %"
  document.getElementById("illumination").textContent = obj.illumination + " lx"

  time = Date.parse(obj.created_at)
  document.getElementById("updated_at").textContent = "Updated " + ((new Date() - time) // 1000) + " seconds ago"

@relay1 = ->

  $.post '/api/states/update',
    JSON.stringify
      relay1_requested: document.getElementById("button_relay1").textContent == "ON" ? true : false
      token: '12345678'


