#ifndef S3EGAMETHRIVE_INTERNAL_WP8_H
#define S3EGAMETHRIVE_INTERNAL_WP8_H

void NotificationReceivedCallback(const char* additionalData, bool isActive);
void TagsReceivedCallback(const char* tags);
void IdsAvailableCallback(const char* playerID, const char* pushToken);

#endif /* S3EGAMETHRIVE_INTERNAL_WP8_H */