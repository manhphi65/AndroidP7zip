package com.hzy.p7zip.app.activity;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.MenuItem;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.google.android.material.navigation.NavigationView;
import com.hzy.libp7zip.P7ZipApi;
import com.hzy.p7zip.app.R;
import com.hzy.p7zip.app.fragment.AboutFragment;
import com.hzy.p7zip.app.fragment.HelpFragment;
import com.hzy.p7zip.app.fragment.StorageFragment;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {
    public static final String TAG = "TOH_MainActivity";
    @BindView(R.id.drawer_layout)
    DrawerLayout drawer;
    @BindView(R.id.toolbar)
    Toolbar toolbar;
    @BindView(R.id.nav_view)
    NavigationView navigationView;

    private Fragment mFragment;
    private FragmentManager mFragmentManager;
    private List<Fragment> mFragmentList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
        initToolbar();
        mFragmentList = new ArrayList<>();
        mFragmentManager = getSupportFragmentManager();
        navigationView.setNavigationItemSelectedListener(this);
        showFragment(StorageFragment.class);

        /*String fileNameforTest =
                //"password23.zip";
                "bigcat.7z";
        //"split_zip_pass1.zip.001";

        String pathForTest = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).getAbsolutePath()
                + File.separatorChar + fileNameforTest;
        Log.d(TAG, "Check file :" + fileNameforTest);
        String testCommand1 = "7z t '" + pathForTest + "'";
        int resultCode1 = P7ZipApi.executeCommand(testCommand1);
        String testCommand2 = "7z t '-p2' '" + pathForTest + "'";
        int resultCode2 = P7ZipApi.executeCommand(testCommand2);
        String testCommand3 = "7z t '-p1' '" + pathForTest + "'";
        int resultCode3 = P7ZipApi.executeCommand(testCommand3);
        Log.d(TAG, "Command line : " + testCommand1 + "\nResult : " + resultCode1);
        Log.d(TAG, "Command line : " + testCommand2 + "\nResult : " + resultCode2);
        Log.d(TAG, "Command line : " + testCommand3 + "\nResult : " + resultCode3);*/

        String fileNameForList =
                //"password23.zip";
                //"bigcat.7z";
                //"split_zip_pass1.zip.001";
                "split_7z_pass1.7z.001";
        String pathForList = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).getAbsolutePath()
                + File.separatorChar + fileNameForList;
        Log.d(TAG, "Check file :" + fileNameForList);
        try {
            /*String listCommand1 = "7z l '" + pathForList + "'";
            String resultList1 = new String(P7ZipApi.executeCommandList(listCommand1), "UTF-32");
            String listCommand2 = "7z l '-p2' '" + pathForList + "'";
            String resultList2 = new String(P7ZipApi.executeCommandList(listCommand2), "UTF-32");*/
            String listCommand3 = "7z l '-p1' '" + pathForList + "'";
            String resultList3 = P7ZipApi.executeCommandList(listCommand3);
            /*Log.d(TAG, "Command line : " + listCommand1 + "\nResult : " + resultList1);
            Log.d(TAG, "Command line : " + listCommand2 + "\nResult : " + resultList2);*/
            Log.d(TAG, "Command line : " + listCommand3 + "\nResult : " + resultList3);
        } catch (Exception e) {

        }

    }

    private void initToolbar() {
        setSupportActionBar(toolbar);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();
    }

    @Override
    public void onBackPressed() {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {
        drawer.closeDrawer(GravityCompat.START);
        int id = item.getItemId();
        switch (id) {
            case R.id.nav_storage:
                showFragment(StorageFragment.class);
                break;
            case R.id.nav_help:
                showFragment(HelpFragment.class);
                break;
            case R.id.nav_about:
                showFragment(AboutFragment.class);
                break;
            case R.id.nav_exit:
                finish();
                break;
        }
        return true;
    }

    private void showFragment(Class<? extends Fragment> fragmentCls) {
        FragmentTransaction transaction = mFragmentManager.beginTransaction();
        if (mFragment != null) {
            transaction.hide(mFragment);
        }
        Fragment newFragment = null;
        for (Fragment f : mFragmentList) {
            if (fragmentCls.isInstance(f)) {
                newFragment = f;
                transaction.show(newFragment);
                break;
            }
        }
        if (newFragment == null) {
            try {
                newFragment = fragmentCls.newInstance();
                transaction.add(R.id.content_main_frame, newFragment);
                mFragmentList.add(newFragment);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        mFragment = newFragment;
        transaction.commitAllowingStateLoss();
    }

}
