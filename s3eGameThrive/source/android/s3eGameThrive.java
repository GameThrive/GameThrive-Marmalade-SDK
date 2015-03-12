/*
java implementation of the s3eGameThrive extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import 	android.app.Activity;

import org.json.JSONException;
import org.json.JSONObject;

import com.gamethrive.GameThrive;
import com.gamethrive.GameThrive.GetTagsHandler;
import com.gamethrive.GameThrive.IdsAvailableHandler;
import com.gamethrive.NotificationOpenedHandler;
// Comment in the following line if you want to use ResourceUtility
// import com.ideaworks3d.marmalade.ResourceUtility;

class s3eGameThrive implements NotificationOpenedHandler {
	
	private GameThrive gameThrive;
	private boolean inited = false;

    public void GameThriveInitialize(String appId, String googleProjectNumber, boolean autoRegister) {
		if (!inited) {
			gameThrive = new GameThrive((Activity)LoaderActivity.m_Activity, googleProjectNumber, appId, this);
			inited = true;
		}
    }
	
	@Override
	public void notificationOpened(String message, JSONObject additionalData, boolean isActive) {
		String extraData = null;
		if (additionalData != null)
			extraData = additionalData.toString();
		
		NotificationReceivedCallback(message, extraData, isActive);
	}
	
	
    public void GameThriveSendTag(String key, String value) {
		gameThrive.sendTag(key, value);
    }
	
    public void GameThriveGetTags() {
		gameThrive.getTags(new GetTagsHandler() {
			@Override
			public void tagsAvailable(JSONObject tags) {
				TagsReceivedCallback(tags.toString());
			}
		});
    }
	
    public void GameThriveDeleteTag(String key, String value) {
        gameThrive.deleteTag(key);
    }
	
    public void GameThriveSendPurchase(double amount) {
        gameThrive.sendPurchase(amount);
    }
	
    public void GameThriveGetIdsAvailable() {
        gameThrive.idsAvailable(new IdsAvailableHandler() {
			@Override
			public void idsAvailable(String playerId, String registrationId) {
				IdsAvailableCallback(playerId, registrationId);
			}
		});
    }
	
	public void GameThriveOnPause() {
		gameThrive.onPaused();
	}
	
	public void GameThriveOnResume() {
		gameThrive.onResumed();
	}

	public void GameThriveEnableVibrate(boolean enable) {
		gameThrive.enableVibrate(enable);
	}

	public void GameThriveEnableSound(boolean enable) {
		gameThrive.enableSound(enable);
	}
	
	public native void NotificationReceivedCallback(String message, String additionalData, boolean isActive);
	public native void IdsAvailableCallback(String playerID, String pushToken);
	public native void TagsReceivedCallback(String tags);
}
