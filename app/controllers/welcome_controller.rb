class WelcomeController < ApplicationController
  def index
    @sensor = Sensor.last


  end
end
