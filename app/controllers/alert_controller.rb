class AlertController < ApplicationController

  def intrusion
    # check request key
    if params[:key] != ENV['APP_KEY']
      render :plain => "invalid key"
      return
    end

    # call opsgenie
    request_body = JSON.generate({
      'apiKey' => ENV['OPSGENIE_API_KEY'],
      'message' => '敵の侵入を検知しました',
      'alias' => 'alert_intrusion',
    })

    uri = URI.parse("https://api.opsgenie.com/v1/json/alert")
    http = Net::HTTP.new(uri.host, uri.port)
    http.use_ssl = true
    http.verify_mode = OpenSSL::SSL::VERIFY_NONE
    req = Net::HTTP::Post.new(uri.path)
    req.body = request_body
    res = http.request(req)

    render :plain => "accept"
  end

end
