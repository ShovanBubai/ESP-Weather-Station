package com.example.myapplication;

import android.graphics.Bitmap;
import android.net.http.SslError;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.SslErrorHandler;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class MainActivity extends AppCompatActivity {
    private WebView mywebView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mywebView=(WebView) findViewById(R.id.webview);
        WebSettings webSettings=mywebView.getSettings();
        mywebView.loadUrl("http://192.168.43.142:80/"); // your adress:port
        webSettings.setJavaScriptEnabled(true);


    }

    public class myWebClient extends WebViewClient{
        @Override
        public void onPageStarted (WebView view, String url, Bitmap favicon) {
            super.onPageStarted(view, url, favicon);
        }

        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url){
            view.loadUrl(url);
            return false;
        }
    }
    @Override
        public void onBackPressed (){
        if (mywebView.canGoBack()){
            mywebView.goBack();}
            else{
                super.onBackPressed();
            }
        }
}
