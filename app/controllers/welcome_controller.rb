class WelcomeController < ApplicationController
  def index
    @sensor = Sensor.last
    @state = State.last

  end
end
