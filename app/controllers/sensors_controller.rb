class SensorsController < ApplicationController

  before_action :check_json!, only: [:create]

  def show
    @sensor = Sensor.order("created_at").last
    render json: @sensor, except: [:updated_at]
  end

  def create
    if @json['token'] != Rails.application.secrets.arduino_token.to_s
      render :nothing => true, status: :unauthorized
    else
      if @json['humidity'] >=0

        if Sensor.create(temperature: @json['temperature'], humidity: @json['humidity'], illumination: @json['illumination'])
          render :nothing => true, status: :ok
        else
          render :nothing => true, status: :bad_request
        end
      end

    end


  rescue
    render :nothing => true, status: :bad_request
  end

  private

  def check_json!
    @json = JSON.parse(request.body.read)
  rescue JSON::ParserError => e
    render :nothing => true,
           status: :bad_request

  end

end
