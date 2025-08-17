% CONFIGURATION
threshold = 28;  % in cm
readChannelID = 3021778;  % your ThingSpeak channel ID
readAPIKey = '0CLSU7M141PUUQAV';  % leave empty if your channel is public

% TELEGRAM CONFIG — replace these
botToken = '7308004226:AAF_25V0EOjECSNNmkCAc9fhrvqCNk7-wxY';  % from BotFather
chatID = '7428619479';      % from getUpdates

% Read latest distance value
data = thingSpeakRead(readChannelID, 'Fields', 1, 'NumPoints', 1, 'ReadKey', readAPIKey);

% Check if distance below threshold
if data <= threshold
    message = sprintf('⚠ Object Alert! Distance: %.2f cm', data);
    url = sprintf('https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s', ...
        botToken, chatID, urlencode(message));
    webread(url);  % Send Telegram alert
end