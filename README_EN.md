# About This Tool
This tool allows you to set **any image** as a map in Minecraft.

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/6f76f898-14b2-4801-b6d9-6be0cc843615" />

---

# How to Use

First, download **CustomMap.dll** from the [latest release page](https://github.com/releases/latest).

<img width="911" height="394" alt="image" src="https://github.com/user-attachments/assets/a0698fbc-3ae4-4e97-9204-2553ed3ccad9" />

After the download is complete, inject the DLL into Minecraft using an injector such as  
[FateInjector](https://github.com/fligger/FateInjector).

Once the injection is complete, open the in-game chat and use the following command:

```
.set_map <map size (128)> <image file path>
```


<img width="772" height="74" alt="image" src="https://github.com/user-attachments/assets/014b37bc-157a-418d-bd02-a3e735cc0d2e" />

**⚠️ Note:**  
If the image path contains quotation marks (`"`), a **Not Found** error will occur.

If the image is set correctly, a message like the one below will be displayed:

<img width="770" height="107" alt="image" src="https://github.com/user-attachments/assets/ee1b167a-b13b-4a06-9a13-fd87724b8fd1" />

After setting the image, create a map using an **empty map** and hold it in your hand.

After waiting for a short time, a message like the one below will appear.  
If you see this message, the process was successful.

<img width="762" height="68" alt="image" src="https://github.com/user-attachments/assets/ffa1e217-36be-4865-9d8d-43393346179b" />

While holding the map, it will appear as a normal map.  
However, once you place it in an item frame or similar, it will switch to the correctly configured image.

---

# Troubleshooting

<details>
<summary><h2>Q. The map reverts to the original terrain display after rejoining the world or over time</h2></summary>

**A.** Create the map and set the image at a location far away (e.g. coordinates around 100,000) that is normally not loaded. This prevents the issue.
</details>

<details>
<summary><h2>Q. No message appears in the bottom-right corner</h2></summary>

**A.** If no message is displayed, the output will be written to `logs.txt` located in the following directory:

```
%APPDATA%\Local\Packages\Microsoft.MinecraftUWP_8wekyb3d8bbwe\RoamingState
```

</details>

Please report bugs and issues via **GitHub Issues**.

---

# Reference
[Shock95 bdsx-image-maps](https://github.com/Shock95/bdsx-image-maps)

---

## Prohibited Actions ⚠️
The following actions are **strictly prohibited**:

- Using or publishing **all or part of the source code** as your own work
- **Redistribution or re-uploading** without permission

> **Note:**  
> “Using as a reference” and “copying for use” are not the same.
>
> When introducing this tool to others, **always use the GitHub URL**.
>
> If you create maps using this tool, please include this tool’s URL in the **credits**.

---

## License
This project is **source-available but NOT open source**.

Unauthorized use or redistribution of the source code is prohibited.  
For details, see [LICENSE](./LICENSE).

---

## Disclaimer
The author assumes **no responsibility** for any damages caused by the use of this tool.
