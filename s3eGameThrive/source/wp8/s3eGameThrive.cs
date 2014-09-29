/*
C# implementation of the s3eGameThrive extension.

Add win8-specific functionality here.

These functions are called via Shim class from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
using System.Windows.Controls;
using Microsoft.Phone.Controls;
using System.Windows.Media;

using s3e_native;
using s3eGameThriveExtension;

using Newtonsoft.Json.Linq;

using GameThriveSDK;
using System.Windows;

namespace s3eGameThriveManaged
{
    public class s3eGameThriveManaged: IManagedS3Es3eGameThriveAPI, IManagedS3EEDKAPI
    {
        

        public bool ExtRegister(IS3EAPIManager apiManager, object mainPage)
        {
            try
            {
                // Keep a reference to the API Manager in order to call other
                // APIs.
                m_APIManager = apiManager;
                m_MainPage = mainPage as PhoneApplicationPage;

                m_MainPanel = VisualTreeHelper.GetChild(m_MainPage, 0) as Panel;

                // Add the managed API to the API Manager
                if (!m_APIManager.RegisterManagedAPI("s3eGameThrive", this))
                    throw new System.Exception("Can't register Managed API");

                // Add the native API to the API manager.  Note that we don't own the native
                // interface, the API Manager does.  We want the two notions of managed and
                // native interface to be separate as there may be cases where we only want
                // one not the other.  It's only a matter of convenience that we create both
                // APIs in this ctr
                m_Native = new s3eGameThriveNativeInterface();
                if (!m_APIManager.RegisterNativeAPI("s3eGameThrive", m_Native))
                    throw new System.Exception("Can't register Native API");

                // Create a Shim so we can pass the Managed interface down to native
                m_Shim = new s3eGameThriveShim();

                // Pass the managed interface down
                m_Shim.Init(this);
            }
            catch (System.Exception e)
            {
                m_APIManager = null;
                m_Shim = null;
                m_Native = null;
                System.Windows.MessageBox.Show("Failed to register s3eGameThrive : " + e.Message);
                
                return false;
            }
            
            return true;
        }
        IS3EAPIManager m_APIManager = null;
        PhoneApplicationPage m_MainPage = null;
        // hint: add UI Elements as children of m_MainPanel
        Panel m_MainPanel = null;
        s3eGameThriveShim m_Shim = null;
        s3eGameThriveNativeInterface m_Native = null;

        // managed platform functionality
		
        public void GameThriveInitialize_managed(string appId)
        {
            GameThrive.Init(appId, (additionalData, isActive) => {
                m_Native.CLR_TO_MARM_NotificationReceivedCallback((additionalData == null) ? "" : JObject.FromObject(additionalData).ToString(), isActive);
            });
        }

        public void GameThriveSendTag_managed(string key, string value)
        {
            GameThrive.SendTag(key, value);
        }

        public void GameThriveGetTags_managed()
        {
            GameThrive.GetTags((tags) => {
                m_Native.CLR_TO_MARM_TagsReceivedCallback((tags == null) ? "" : JObject.FromObject(tags).ToString());
            });
        }

        public void GameThriveDeleteTag_managed(string key)
        {
            GameThrive.DeleteTag(key);
        }

        public void GameThriveSendPurchase_managed(double amount)
        {
            GameThrive.SendPurchase(amount);
        }

        public void GameThriveGetIdsAvailable_managed()
        {
            GameThrive.GetIdsAvailable((playerID, channelUri) => {
                m_Native.CLR_TO_MARM_IdsAvailableCallback(playerID, (channelUri == null) ? "" : channelUri);
            });
        }
    }
}
