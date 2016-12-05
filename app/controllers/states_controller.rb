class StatesController < ApplicationController
  before_action :check_json!, only: [:update]

  def show
    @state = State.last
    render json: @state, except: [:created_at, :id]
  end

  def update
    if @json['token'] != Rails.application.secrets.arduino_token.to_s
      render :nothing => true, status: :unauthorized

    else
      @json.delete('token')
      if State.last.update(@json)
        render :nothing => true, status: :ok
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
